import os
import subprocess

programs_dir = "programs"
# For Unix-like systems -- change as needed
executable = "./saml"

try:
  subprocess.run(['ocamlc', '-c', 'desugar.ml'], check=True, capture_output=True)
  subprocess.run(['ocamlc', '-c', 'parser.mli'], check=True, capture_output=True)
  subprocess.run(['ocamlc', '-c', 'lexer.ml'], check=True, capture_output=True)
  subprocess.run(['ocamlc', '-c', 'parser.ml'], check=True, capture_output=True)
  subprocess.run(['ocamlc', '-c', 'interpret.ml'], check=True, capture_output=True)
  subprocess.run(['ocamlc', '-c', 'evaluator.ml'], check=True, capture_output=True)
  subprocess.run(['ocamlc', '-o', executable, 'lexer.cmo', 'parser.cmo', 'desugar.cmo', 'interpret.cmo', 'evaluator.cmo'], check=True, capture_output=True)
except subprocess.CalledProcessError as e:
  print(f"Error with compilation:\n{e.stderr}")
  exit(1)

if not os.path.isdir(programs_dir):
    print(f"Error: Directory '{programs_dir}' does not exist.")
    exit(1)

for filename in os.listdir(programs_dir):
    file_path = os.path.join(programs_dir, filename)
    
    if os.path.isfile(file_path):
        try:
            print(f"Running on {filename}...")
            result = subprocess.run([executable, file_path], check=True, capture_output=True, text=True)
            print(f"Output:\n{result.stdout}")
        except subprocess.CalledProcessError as e:
            print(f"Error interpreting {filename}:\n{e.stderr}")
