sample_size = 10

'''
question (a) 
'''
print("question (a)")
mu_list = [0.05, 0.6, 0.9]
pbb_list = []

for mu in mu_list:
    pbb = (1 - mu) ** sample_size
    print(f'when mu is {mu}, probability of no red marbles is :{pbb}')
    pbb_list.append(pbb)

'''
question (b)
'''
print("\nquestion (b)")
sample_num = 1000

for i, mu in enumerate(mu_list):
    pbb_all_have_red = (1 - pbb_list[i]) ** sample_num # the probability of having red marble in all samples
    pbb_have_no_red = 1 - pbb_all_have_red
    print(f'when mu is {mu}, and sample number is {sample_num}, probability of at least one has no red marbles is :{pbb_have_no_red}')

'''
question (c)
'''
print("\nquestion (c)")
sample_num = 1000000

for i, mu in enumerate(mu_list):
    pbb_all_have_red = (1 - pbb_list[i]) ** sample_num # the probability of having red marble in all samples
    pbb_have_no_red = 1 - pbb_all_have_red
    print(f'when mu is {mu}, and sample number is {sample_num}, probability of at least one has no red marbles is :{pbb_have_no_red}')



    
