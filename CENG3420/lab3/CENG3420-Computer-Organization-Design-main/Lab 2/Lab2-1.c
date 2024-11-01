/***************************************************************/
/*                                                             */
/*                  RISCV-LC Assembler                         */
/*                                                             */
/*                     CEG3420 Lab2                            */
/*                 cbai@cse.cuhk.edu.hk                        */
/*           The Chinese University of Hong Kong               */
/*                                                             */
/***************************************************************/


#include "asm.h"


int reg_to_num(char *reg, int line_no) {
	if (is_reg(reg) == MIS_MATCH)
		handle_err(7, line_no);
	size_t len_of_regs_code = sizeof(arch_regs_encode) / sizeof(arch_regs_encode[0]);
	for (int i = 0; i < len_of_regs_code; i++) {
		if (cmp_str(arch_regs[i], reg))
			return arch_regs_encode[i];
	}
}


int is_imm_in_range(int val, int width) {
	/*
	 * given a bit width, check whether it can hold the signed value
	 */
	// return (val <= ((1 << width) - 1) && val >= -(1 << width));
	return val <= ((1 << (width - 1)) - 1) && (val >= (-(1 << (width - 1))));
}


int handle_label_or_imm(char *val, struct_label_table *label_table, int cmd_no, int line_no) {
	int _val, ret;
	if ((ret = is_imm(val)) == MIS_MATCH) {
		// label
		return label_to_num(val, 20, label_table, cmd_no, line_no);
	} else {
		// immediate value
		_val = (int)strtol(val, NULL, (ret == HEX) ? 16 : 10);
		if (is_imm_in_range(_val, 19))
			return _val;
		else
			handle_err(5, line_no);
	}
}


int validate_imm(char *imm, int width, int line_no) {
	/*
	 * do the base conversion or given a bit width,
	 * validate whether it can hold the immediate value
	 */
	int val, ret;
	if ((ret = is_imm(imm)) == MIS_MATCH)
		handle_err(7, line_no);
	else
	    val = (int)strtol(imm, NULL, (ret == HEX) ? 16 : 10);
	if (width != -1) {
		if (is_imm_in_range(val, width))
			return val;
		else
			handle_err(3, line_no);
	} else
		return val;
}


int lower5bit(char *imm, int line_no) {
	int val = 0, ret;
	if ((ret = is_imm(imm)) == MIS_MATCH)
		handle_err(7, line_no);
	else
		val = ((int)strtol(imm, NULL, (ret == HEX) ? 16 : 10) & 0x1F);
	if (is_imm_in_range(val, 6))
		return val;
	else
		handle_err(5, line_no);
}


int label_to_num(char *label, int width, struct_label_table *label_table, int cmd_no, int line_no) {
	if (is_label(label) != VALID_LABEL)
		handle_err(10, line_no);
	struct_label_table *head_of_label_table = label_table;
	while (*(head_of_label_table->label) != '\0') {
		if (cmp_str(head_of_label_table->label, label)) {
			int offset = head_of_label_table->address;
			/*
			 * refer to `calc_la`
			 */
			if (head_of_label_table->fill)
				offset += la_cnt;
			else
				offset += la_inst[cmd_no];
			/*
			 * each instruction is 32-bit, i.e., 4 byte,
			 * so the offset is shifted left with 2.
			 */
			offset <<= 2;
			if (!is_imm_in_range(offset, width))
				handle_err(8, line_no);
			return offset;
		}
		head_of_label_table++;
	}
	handle_err(1, line_no);
}


struct_regs_indirect_addr* parse_regs_indirect_addr(char *arg2, int line_no) {
	struct_regs_indirect_addr* ret;
	char *reg, *imm;
	char temp[MAX_LINE_LENGTH + 1];
	int i = 0;
	if ((ret = (struct_regs_indirect_addr *)malloc(sizeof(ret))) == NULL)
		handle_err(11, line_no);
	while (arg2[i] != '\0') {
		temp[i] = arg2[i];
		i++;
	}
	temp[i] = '\0';
	imm = strtok(temp, "( ");
	ret->imm = validate_imm(imm, 12, line_no);
	reg = strtok(NULL, ")");
	copy_str(ret->reg, reg);
	return ret;
}


void handle_pseudo_inst(
	FILE *output_file,
	int line_no,
	int cmd_no,
	char *opcode,
	char *arg1,
	char *arg2,
	char *arg3,
	struct_label_table *label_table
) {
	if (is_opcode(opcode) == LA) {
		/*
		 * LA is translated to lui and addi.
		 */
		char temp1[MAX_LINE_LENGTH + 1], temp2[MAX_LINE_LENGTH + 1];
		int i = 0;
		/*
		 * lui is performed first.
		 * the offset is a 20-bit higher number.
		 */
		fprintf(
			output_file,
			"0x%08x\n",
			inst_to_binary(line_no, cmd_no, "lui", arg1, arg2, arg3, label_table)
		);
		while (arg1[i] != '\0') {
			temp1[i] = arg1[i];
			i++;
		}
		temp1[i] = '\0';
		/*
		 * addi is performed first.
		 * the offset is a 12-bit lower number.
		 */
		sprintf(
			temp2,
			"%d",
			(handle_label_or_imm(arg2, label_table, cmd_no, line_no)) & 0xFFF
		);
		fprintf(
			output_file,
			"0x%08x\n",
			inst_to_binary(line_no, cmd_no, "addi", arg1, temp1, temp2, label_table)
		);
	} else if (is_opcode(opcode) == FILL) {
		fprintf(output_file, "0x%08x\n", validate_imm(arg1, 31, line_no));
	} else if (is_opcode(opcode) == HALT) {
		/*
		 * HALT is mapped to the fixed binary
		 */
		fprintf(output_file, "0x%08x\n", 0x0000707f);
	}
}


int inst_to_binary(
	int line_no,
	int cmd_no,
	char *opcode,
	char *arg1,
	char *arg2,
	char *arg3,
	struct_label_table *label_table
) {
	/* save the translated machine binary */
	int binary = 0;

	// Integer Register-Immediate Instructions
	if (is_opcode(opcode) == ADDI) {
		binary = (0x04 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (MASK11_0(validate_imm(arg3, 12, line_no)) << 20);
	} else if (is_opcode(opcode) == SLLI) {
		binary = (0x01 << 12) + (0x04 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += ((validate_imm(arg3, 12, line_no) & 0x1F)  << 20);
	} else if (is_opcode(opcode) == XORI) {
		binary = (0x04 << 12) + (0x04 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (MASK11_0(validate_imm(arg3, 12, line_no)) << 20);
	} else if (is_opcode(opcode) == SRLI) {
		binary = (0x05 << 12) + (0x04 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (lower5bit(arg3, line_no) << 20);
	} else if (is_opcode(opcode) == SRAI) {
		binary = (0x10 << 26) + (0x05 << 12) + (0x04 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (lower5bit(arg3, line_no) << 20);
	} else if (is_opcode(opcode) == ORI) {
		binary = (0x06 << 12) + (0x04 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (MASK11_0(validate_imm(arg3, 12, line_no)) << 20);
	} else if (is_opcode(opcode) == ANDI) {
		binary = (0x07 << 12) + (0x04 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (MASK11_0(validate_imm(arg3, 12, line_no)) << 20);
	} else if (is_opcode(opcode) == LUI) {
		binary = (0x0D << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (handle_label_or_imm(arg2, label_table, cmd_no, line_no) & 0xFFFFF000);
	}

	// Integer Register-Register Operations
	else if (is_opcode(opcode) == ADD) {
		binary = (0x0C << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (reg_to_num(arg3, line_no) << 20);
	} else if (is_opcode(opcode) == SUB) {
		binary = (0x20 << 25) + (0x0C << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (reg_to_num(arg3, line_no) << 20);
	} else if (is_opcode(opcode) == SLL) {
		binary = (0x01 << 12) + (0x0C << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (reg_to_num(arg3, line_no) << 20);
	} else if (is_opcode(opcode) == XOR) {
		binary = (0x04 << 12) + (0x0C << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (reg_to_num(arg3, line_no) << 20);
	} else if (is_opcode(opcode) == SRL) {
		binary = (0x05 << 12) + (0x0C << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (reg_to_num(arg3, line_no) << 20);
	} else if (is_opcode(opcode) == SRA) {
		binary = (0x20 << 25) + (0x05 << 12) + (0x0C << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (reg_to_num(arg3, line_no) << 20);
	} else if (is_opcode(opcode) == OR) {
		binary = (0x06 << 12) + (0x0C << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (reg_to_num(arg3, line_no) << 20);
	} else if (is_opcode(opcode) == AND) {
		binary = (0x07 << 12) + (0x0C << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		binary += (reg_to_num(arg2, line_no) << 15);
		binary += (reg_to_num(arg3, line_no) << 20);
	}


	// Unconditional Jumps
	else if (is_opcode(opcode) == JALR) {
		binary = (0x19 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		struct_regs_indirect_addr* ret = parse_regs_indirect_addr(arg2, line_no);
		binary += (reg_to_num(ret->reg, line_no) << 15);
		binary += (ret->imm << 20);
	} else if (is_opcode(opcode) == JAL) {
		binary = (0x1B << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		int offset;
		offset = handle_label_or_imm(arg2, label_table, cmd_no, line_no);
		// imm[19:12]
		binary += (offset & 0xFF000);
		// imm[11]
		binary += ((offset & 0x800) << 9);
		// imm[10:1]
		binary += ((offset & 0x7FE) << 20);
		// imm[20]
		binary += ((offset & 0x100000) << 11);
	}

	// Conditional Branches
	else if (is_opcode(opcode) == BEQ) {
		binary = (0x18 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 15);
		binary += (reg_to_num(arg2, line_no) << 20);
		int offset;
		offset = label_to_num(arg3, 12, label_table, cmd_no, line_no);
		// imm[11]
		binary += ((offset & 0x800) >> 4);
		// imm[4:1]
		binary += ((offset & 0x1E) << 7);
		// imm[10:5]
		binary += ((offset & 0x7E0) << 20);
		// imm[12]
		binary += ((offset & 0x1000) << 19);
	} else if (is_opcode(opcode) == BNE) {
		binary = (0x01 << 12) + (0x18 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 15);
		binary += (reg_to_num(arg2, line_no) << 20);
		int offset;
		offset = label_to_num(arg3, 12, label_table, cmd_no, line_no);
		// imm[11]
		binary += ((offset & 0x800) >> 4);
		// imm[4:1]
		binary += ((offset & 0x1E) << 7);
		// imm[10:5]
		binary += ((offset & 0x7E0) << 20);
		// imm[12]
		binary += ((offset & 0x1000) << 19);
	} else if (is_opcode(opcode) == BLT) {
		binary = (0x04 << 12) + (0x18 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 15);
		binary += (reg_to_num(arg2, line_no) << 20);
		int offset;
		offset = label_to_num(arg3, 12, label_table, cmd_no, line_no);
		// imm[11]
		binary += ((offset & 0x800) >> 4);
		// imm[4:1]
		binary += ((offset & 0x1E) << 7);
		// imm[10:5]
		binary += ((offset & 0x7E0) << 20);
		// imm[12]
		binary += ((offset & 0x1000) << 19);
	} else if (is_opcode(opcode) == BGE) {
		binary = (0x05 << 12) + (0x18 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 15);
		binary += (reg_to_num(arg2, line_no) << 20);
		int offset;
		offset = label_to_num(arg3, 12, label_table, cmd_no, line_no);
		// imm[11]
		binary += ((offset & 0x800) >> 4);
		// imm[4:1]
		binary += ((offset & 0x1E) << 7);
		// imm[10:5]
		binary += ((offset & 0x7E0) << 20);
		// imm[12]
		binary += ((offset & 0x1000) << 19);
	}

	// Load and Store Instructions
	else if (is_opcode(opcode) == LB) {
		binary = 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		struct_regs_indirect_addr* ret = parse_regs_indirect_addr(arg2, line_no);
		binary += (reg_to_num(ret->reg, line_no) << 15);
		binary += (ret->imm << 20);
	} else if (is_opcode(opcode) == LH) {
		binary = (0x01 << 12) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		struct_regs_indirect_addr* ret = parse_regs_indirect_addr(arg2, line_no);
		binary += (reg_to_num(ret->reg, line_no) << 15);
		binary += (ret->imm << 20);
	} else if (is_opcode(opcode) == LW) {
		binary = (0x02 << 12) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 7);
		struct_regs_indirect_addr* ret = parse_regs_indirect_addr(arg2, line_no);
		binary += (reg_to_num(ret->reg, line_no) << 15);
		binary += (ret->imm << 20);
	} else if (is_opcode(opcode) == SB) {
		binary = (0x08 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 20);
		struct_regs_indirect_addr* ret = parse_regs_indirect_addr(arg2, line_no);
		binary += (reg_to_num(ret->reg, line_no) << 15);
		// imm[4:0]
		binary += ((ret->imm & 0x1F) << 7);
		// imm[11:5]
		binary += ((ret->imm & 0xFE0) << 20);
	} else if (is_opcode(opcode) == SH) {
		binary = (0x01 << 12) + (0x08 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 20);
		struct_regs_indirect_addr* ret = parse_regs_indirect_addr(arg2, line_no);
		binary += (reg_to_num(ret->reg, line_no) << 15);
		// imm[4:0]
		binary += ((ret->imm & 0x1F) << 7);
		// imm[11:5]
		binary += ((ret->imm & 0xFE0) << 20);
	} else if (is_opcode(opcode) == SW) {
		binary = (0x02 << 12) + (0x08 << 2) + 0x03;
		binary += (reg_to_num(arg1, line_no) << 20);
		struct_regs_indirect_addr* ret = parse_regs_indirect_addr(arg2, line_no);
		binary += (reg_to_num(ret->reg, line_no) << 15);
		// imm[4:0]
		binary += ((ret->imm & 0x1F) << 7);
		// imm[11:5]
		binary += ((ret->imm & 0xFE0) << 20);
	}
	return binary;
}


int is_label(char *ptr) {
	if (*ptr == '\0')
		return MIS_MATCH;

	char *label = ptr;
	if (
		is_opcode(label) == MIS_MATCH && \
		is_reg(ptr) == MIS_MATCH && \
		is_imm(ptr) == MIS_MATCH && \
		is_regs_indirect_addr(ptr) == MIS_MATCH
	) {
		if (isdigit(*label))
			return INVALID_LABEL;
		else {
			label++;
			while (label != NULL && *label != '\0') {
				/* all characters have been converted to lower-case */
				if (isalnum(*label) || *label == '_') {
					label++;
					continue;
				}
				else
					return INVALID_LABEL;
			}
		}
		return VALID_LABEL;
	} else
		return INVALID_LABEL;
}


int is_opcode(char *ptr) {
	if (*ptr == '\0')
		return MIS_MATCH;

	size_t len_of_opcode_table = sizeof(opcode_table) / sizeof(opcode_table[0]);
	for (int i = 0; i < (int)len_of_opcode_table; i++) {
		if (cmp_str(opcode_table[i], ptr)) {
			/* i is equal to the enumeration of opcodes */
			return i;
		}
	}
	/* if the opcode is invalid */
	return MIS_MATCH;
}


int is_reg(char *ptr) {
	if (*ptr == '\0')
		return MIS_MATCH;

	size_t len_of_arch_regs = sizeof(arch_regs) / sizeof(arch_regs[0]);
	for (int i = 0; i < (int)len_of_arch_regs; i++) {
		if (cmp_str(arch_regs[i], ptr)) {
			/* it is an architecture register */
			return ARCH_REGS;
		}
	}
	return MIS_MATCH;
}


int is_imm(char *ptr) {
	/* -0x7, 0x7, -7, 7 */
	if (*ptr == '\0')
		return MIS_MATCH;

	int i = 0, l = strlen(ptr);
	bool hex = false;
	if (l > 3 && ptr[0] == '-' && ptr[1] == '0' && (tolower(ptr[2]) == 'x')) {
		i += 3;
		hex = true;
	} else if (l > 2 && ptr[0] == '0' && (tolower(ptr[1]) == 'x')) {
		i += 2;
		hex = true;
	} else if (l > 1 && ptr[0] == '-') {
		i += 1;
	}
	while (i < l && isxdigit(ptr[i]))
		i++;
	if (i == l) {
		if (hex)
			return HEX;
		else
			return DEC;
	} else
		return MIS_MATCH;
}


int is_regs_indirect_addr(char *ptr) {
	if (*ptr == '\0')
		return MIS_MATCH;

	char *imm = NULL, *reg = NULL, *_ptr = NULL;
	int i = 0;
	if (!(imm = (char *)malloc((strlen(ptr) + 1) * sizeof(char))))
		error("malloc is failed in 'is_regs_indirect_addr'.\n");
	if (!(reg = (char *)malloc((strlen(ptr) + 1) * sizeof(char))))
		error("malloc is failed in 'is_regs_indirect_addr'.\n");
	memset(imm, '\0', strlen(ptr));
	memset(reg, '\0', strlen(ptr));
	_ptr = ptr;
	/* parse imm. */
	while (*_ptr != '\0' && *_ptr != '(') {
		if (*_ptr != ' ' && *_ptr != '\t')
			imm[i++] = *_ptr;
		_ptr++;
	}
	imm[i] = '\0';
	if (*_ptr == '\0') {
		free(imm);
		free(reg);
		return MIS_MATCH;
	}
	_ptr++;
	i = 0;
	/* parse reg. */
	while (*_ptr != '\0' && *_ptr != ')') {
		if (*_ptr != ' ' && *_ptr != '\t')
			reg[i++] = *_ptr;
		_ptr++;
	}
	reg[i] = '\0';
	if (is_imm(imm) != MIS_MATCH && is_reg(reg) != MIS_MATCH) {
		free(imm);
		free(reg);
		return REGS_INDIRECT_ADDR;
	}
	else {
		free(imm);
		free(reg);
		return MIS_MATCH;
	}
}


int is_arg(char *ptr) {
	if (*ptr == '\0')
		return MIS_MATCH;

	if (is_label(ptr) == VALID_LABEL)
		return VALID_LABEL;
	if (is_reg(ptr) != MIS_MATCH)
		return ARCH_REGS;
	else if (is_imm(ptr) != MIS_MATCH)
		return IMM;
	else if (is_regs_indirect_addr(ptr) != MIS_MATCH)
		return REGS_INDIRECT_ADDR;
	else
		return REGS_INDIRECT_ADDR;
}


void calc_la(FILE *input_file) {
	/*
	 * each pseudo-instruction LA is translated to Lui and addi,
	 * i.e., two instructions, so we should count them first to
	 * correctly know the offset of other instructions.
	 */
	char line[MAX_LINE_LENGTH + 1];
	char *ptr;
	int line_cnt = 0, k = 0;

	/* re-read the input file */
	rewind(input_file);
	while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
		for (int i = 0; i < strlen(line); i++)
			line[i] = tolower(line[i]);
		ptr = line;
		while (*ptr != '#' && *ptr != '\0' && *ptr != '\n' && *ptr != '\r')
			ptr++;
		*ptr = '\0';
		if (!(ptr = strtok(line, "\t\n ,")))
			continue;
		if (is_opcode(ptr) == LA)
			la_inst[line_cnt] = ++k;
		else {
			if (!(ptr = strtok(NULL, "\t\n ,")))
				continue;
			if (is_opcode(ptr) == LA)
				la_inst[line_cnt] = ++k;
			else
				la_inst[line_cnt] = k;
		}
		line_cnt++;
	}
	la_cnt = k;
}


int parse_inst(
	FILE *input_file,
	char **label,
	char **opcode,
	char **arg1,
	char **arg2,
	char **arg3
) {
	char *ptr;
	int i;

	char *line, *_line;
	if (!(line = malloc(sizeof(char) * (MAX_LINE_LENGTH + 1))))
		error("malloc is failed in 'parse_inst'.\n");

	if (!fgets(line, MAX_LINE_LENGTH, input_file))
		return(END_OF_FILE);

	/* convert the entire line to lowercase characters */
	for (i = 0; i < strlen(line); i++)
		line[i] = tolower(line[i]);

	/* make the pointers point to the address of the end, i.e., '\0' */
	*label = *opcode = *arg1 = *arg2 = *arg3 = line + strlen(line);

	/* ignore the comments */
	ptr = strstr(line, "#");
	if (ptr)
		*ptr = '\0';
	ptr = line;
	while (*ptr == ' ' || *ptr == '\n' || *ptr == '\r')
		ptr++;

	if (!strlen(ptr))
		return(COMMENT_LINE);

	if (!(_line = (char *)malloc((strlen(line) + 1) * sizeof(char))))
		error("malloc is failed in 'parse_inst'.\n");
	copy_str(_line, line);
	/* skip blank spaces at the beginning of the line */
	if (!(ptr = strtok(_line, "\t\n ,")))
		return(DONE);
	i = 1;
	while (strtok(NULL, "\t\n ,"))
		i++;
	switch(i) {
		case 1:
				ptr = strtok(line, "\t\n ,");
				assert(
					cmp_str(opcode_table[30], ptr),
					"halt is expected in the input asm source code.\n"
				);
				*opcode = ptr;
				break;
		case 2:
				ptr = strtok(line, "\t\n ,");
				assert(
					is_label(ptr) == VALID_LABEL,
					"a valid label is expected in the input asm source code.\n"
				);
				*label = ptr;
				ptr = strtok(NULL, "\t\n ,");
				assert(
					cmp_str(opcode_table[30], ptr),
					"halt is expected in the input asm source code.\n"
				);
				*opcode = ptr;
				break;
		case 3:
				ptr = strtok(line, "\t\n ,");
				if (is_label(ptr) == VALID_LABEL) {
					*label = ptr;
					ptr = strtok(NULL, "\t\n ,");
					assert(
						is_opcode(ptr) != MIS_MATCH,
						"a valid label is expected in the input asm source code.\n"
					);
					*opcode = ptr;
					ptr = strtok(NULL, "\t\n ,");
					assert(
						is_arg(ptr) != MIS_MATCH,
						"opcode is expected in the input asm source code.\n"
					);
					*arg1 = ptr;
				} else {
					assert(
						is_opcode(ptr) != MIS_MATCH,
						"opcode is expected in the input asm source code.\n"
					);
					*opcode = ptr;
					ptr = strtok(NULL, "\t\n ,");
					assert(
						is_arg(ptr) != MIS_MATCH,
						"argument is expected in the input asm source code.\n"
					);
					*arg1 = ptr;
					ptr = strtok(NULL, "\t\n ,");
					assert(
						is_arg(ptr) != MIS_MATCH,
						"argument is expected in the input asm source code.\n"
					);
					*arg2 = ptr;
				}
				break;
		case 4:
				ptr = strtok(line, "\t\n ,");
				if (is_label(ptr) == VALID_LABEL) {
					*label = ptr;
					ptr = strtok(NULL, "\t\n ,");
					assert(
						is_opcode(ptr) != MIS_MATCH,
						"a valid label is expected in the input asm source code.\n"
					);
					*opcode = ptr;
					ptr = strtok(NULL, "\t\n ,");
					assert(
						is_arg(ptr) != MIS_MATCH,
						"opcode is expected in the input asm source code.\n"
					);
					*arg1 = ptr;
					ptr = strtok(NULL, "\t\n ,");
					assert(
						is_arg(ptr) != MIS_MATCH,
						"argument is expected in the input asm source code.\n"
					);
					*arg2 = ptr;
				} else {
					assert(
						is_opcode(ptr) != MIS_MATCH,
						"opcode is expected in the input asm source code.\n"
					);
					*opcode = ptr;
					ptr = strtok(NULL, "\t\n ,");
					assert(
						is_arg(ptr) != MIS_MATCH,
						"opcode is expected in the input asm source code.\n"
					);
					*arg1 = ptr;
					ptr = strtok(NULL, "\t\n ,");
					assert(
						is_arg(ptr) != MIS_MATCH,
						"argument is expected in the input asm source code.\n"
					);
					*arg2 = ptr;
					ptr = strtok(NULL, "\t\n ,");
					assert(
						is_arg(ptr) != MIS_MATCH,
						"argument is expected in the input asm source code.\n"
					);
					*arg3 = ptr;
				}
				break;
		case 5:
				ptr = strtok(line, "\t\n ,");
				assert(
					is_label(ptr) == VALID_LABEL,
					"a valid label is expected in the input asm source code.\n"
				);
				*label = ptr;
				ptr = strtok(NULL, "\t\n ,");
				assert(
					is_opcode(ptr) != MIS_MATCH,
					"a valid label is expected in the input asm source code.\n"
				);
				*opcode = ptr;
				ptr = strtok(NULL, "\t\n ,");
				assert(
					is_arg(ptr) != MIS_MATCH,
					"opcode is expected in the input asm source code.\n"
				);
				*arg1 = ptr;
				ptr = strtok(NULL, "\t\n ,");
				assert(
					is_arg(ptr) != MIS_MATCH,
					"argument is expected in the input asm source code.\n"
				);
				*arg2 = ptr;
				ptr = strtok(NULL, "\t\n ,");
				assert(
					is_arg(ptr) != MIS_MATCH,
					"argument is expected in the input asm source code.\n"
				);
				*arg3 = ptr;
				break;
		default:
				error("source codes contain errors.\n");
	}
	return(DONE);
}


void handle_err(int err_no, int line_no) {
	switch (err_no) {
		case 1:
			error("<error no: 1> undefeind label in the line %d.\n", line_no + 1);
			exit(1);
		case 2:
			error("<error no: 2> invalid opcode in the line %d.\n", line_no + 1);
			exit(2);
		case 3:
			error("<error no: 3> invalid constant in the line %d.\n", line_no + 1);
			exit(3);
		case 4:
			error("<error no: 4> invalid register operand in the line %d.\n", line_no + 1);
			exit(4);
		case 5:
			error("<error no: 5> wrong number of operands in the line %d.\n", line_no + 1);
			exit(5);
		case 6:
			error("<error no: 6> unexpected error occurs in the line %d.\n", line_no + 1);
			exit(6);
		case 7:
			error("<error no: 7> unexpected operand in the line %d.\n", line_no + 1);
			exit(7);
		case 8:
			error("<error no: 8> the address of the label in the line %d cannot be fetched.\n", line_no + 1);
			exit(8);
		case 9:
			error("<error no: 9> the memory address in the line %d is invalid to load the program.\n", line_no + 1);
			exit(9);
		case 10:
			error("<error no: 10> the label name in line %d is invalid.\n", line_no + 1);
			exit(10);
		/* reserved for other Error Code */
		case 11:
			error("<error no: 11> malloc is failed in the line %d.\n", line_no + 1);
			exit(11);
		default:
			printf("<error no: 12> unexpected error cannot be handled.\n");
			exit(12);
	}
}


void assemble(char *input_file_name, char *output_file_name) {
	FILE *input_file = open(input_file_name, "r");
	FILE *output_file = open(output_file_name, "w");
	char *label, *opcode, *arg1, *arg2, *arg3;
	int ret;
	int cmd_cnt = 0;
	int line_cnt = 0;
	struct_label_table label_table[MAX_LABELS], *head_of_label_table = label_table;
	int i, j;

	/* initialize `label_table` */
	for (i = 0; i < MAX_LABELS; i++, head_of_label_table++)
		head_of_label_table->label[0] = '\0';
	head_of_label_table = label_table;

	printf("Processing input file %s\n", input_file_name);
	printf("Writing result to output file %s\n", output_file_name);

	/* handle all labels in the input file */
	do {
		ret = parse_inst(input_file, &label, &opcode, &arg1, &arg2, &arg3);
		if (ret != END_OF_FILE && ret != COMMENT_LINE) {
			if (label != NULL && label[0] != '\0') {
				int i = is_label(label);
				if (i == VALID_LABEL) {
					/* check duplicated cases */
					for (j = 0; j < MAX_LABELS; j++) {
                        if (label_table[j].label[0] == '\0')
                        	continue;
						if (cmp_str(label, label_table[j].label))
							/* a conflict occurs with duplicated labels */
							error(
								"line %d, current label '%s' has a conflict with other labels in line %d.\n",
								line_cnt + 1, label, label_table[j].line_cnt
							);
					}
					/* add `label` to `head_of_label_table` */
					if (is_opcode(opcode) == FILL)
						head_of_label_table->fill = true;
					else
						head_of_label_table->fill = false;
					copy_str(head_of_label_table->label, label);
					head_of_label_table->address = cmd_cnt;
					head_of_label_table->line_cnt = line_cnt + 1;
					head_of_label_table++;
				} else
					error("line %d, the label '%s' is invalid.\n", line_cnt + 1, label);
			}
			cmd_cnt++;
		}
		line_cnt++;
	} while (ret != END_OF_FILE);

	cmd_cnt = 0;
	line_cnt = 0;

	calc_la(input_file);

	/* re-read the input file */
	rewind(input_file);
	do {
		ret = parse_inst(input_file, &label, &opcode, &arg1, &arg2, &arg3);
		if (ret != END_OF_FILE && ret != COMMENT_LINE) {
			/* check labels with nothing followed */
			if (is_opcode(opcode) == LA || is_opcode(opcode) == FILL || is_opcode(opcode) == HALT)
				handle_pseudo_inst(
					output_file,
					line_cnt,
					cmd_cnt,
					opcode,
					arg1,
					arg2,
					arg3,
					label_table
				);
			else
				fprintf(
					output_file,
					"0x%08x\n",
					inst_to_binary(
						line_cnt,
						cmd_cnt,
						opcode,
						arg1,
						arg2,
						arg3,
						label_table
					)
				);
			#ifdef DEBUG
				unsigned int code = inst_to_binary(line_cnt, cmd_cnt, opcode, arg1,
					arg2, arg3, label_table);
				printf("[DEBUG] line: %s\tlLabel: %s\n", line, label);
				printf("        opcode: %s\tlArg1: %s\n", opcode, arg1);
				printf("        arg2: %s\tlArg3: %s\n", arg2, arg3);
				printf("        code: 0x%08x\n", code);
			#endif
			cmd_cnt++;
		}
		line_cnt++;
	} while (ret != END_OF_FILE);

	close(input_file);
	close(output_file);
}


int main(int argc, char *argv[]) {
	if (argc != 3) {
		warn("Usage: asm <path to *.asm> <path to *.bin>\n");
		error("%s: error: lack of input file or output file.\n", argv[0]);
	}

	assemble(argv[1], argv[2]);

	return 0;
}
