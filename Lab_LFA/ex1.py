def load_matrix(file:str, matrix_selector=0):
    with open(file, 'r') as f:
        content = f.read()
        matrix_list=[]
        while not content.find('matrix') == -1:
            start = content.find('matrix {') + len('matrix {')
            end = content.find('}', start)
            mat = content[start:end].strip().split('\n')
            new_mat=[]
            for line in mat:
                new_mat.append([int(x) for x in line.strip().split()]) 
            matrix_list.append(new_mat)
            new_content=content[end:]
            content=new_content
        print(matrix_list[matrix_selector])   

def save_matrix(file, matrix):
    matrix_buffer="matrix {\n"
    for line in matrix:
            for element in line:
                matrix_buffer+= f'{element} '
            matrix_buffer+='\n'
    matrix_buffer += "}\n"

    with open(file, 'a') as f:
        f.write(matrix_buffer)
        

load_matrix("data.txt", matrix_selector=1)
