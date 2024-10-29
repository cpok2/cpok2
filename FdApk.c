# V1
import os
import marshal
import random
import string
R = '\x1b[1;31m'  
G = '\x1b[1;32m'  
Y = '\x1b[1;33m' 
EN = 1  
def encrypt_line(line):
    return f"exec(marshal.loads({repr(marshal.dumps(line.encode('utf-8')))}))"
def multi_encrypt(code, layers=10):
    for _ in range(layers):
        lines = code.splitlines()
        compiled_lines = []*1
        for line in lines:
            line = line.strip()*1
            if (
                line.startswith("import") or 
                line.startswith(f"\"") or 
                line.startswith("from") or 
                'input' in line or 
                'print' in line or 
                line.startswith('#') or 
                'x00exec(marshal.loads(' in line           
            ):
                compiled_lines.append(encrypt_line(line))
            elif line:
                compiled_lines.append(f"exec(compile({repr(line)}, '<@sis_c>', 'single'))") 
        code = "\n".join(compiled_lines) 
    return code
if EN == 1:
    file = "q.py"
    try:
        with open(file, 'r') as f:
            code = f.read()        
        encrypted_code = multi_encrypt(code)
        marshaled_data = marshal.dumps(encrypted_code.encode('utf-8'))
        output_file = file.replace('.py', '.py')
        
        with open(output_file, 'w') as f_out:
            f_out.write(f'import marshal\n')
            f_out.write(f'code = marshal.loads({repr(marshaled_data)})\n')
            f_out.write(f'exec(code)\n')
        
        print(G + f'The name of the new encrypted file: {output_file}')
#        import os;os.system('python /sdcard/تشفيراتي-الجديدة/n.py')
        
    except Exception as e:
        print(R + str(e))
else:
    file = input(Y + 'Enter the file name: ')
    os.system(f'py_compile.compile("{file}")')
    print(G + f'The name of the new encrypted file: {file}c')
    
