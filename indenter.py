src_string = ''

with open('subject.c', 'r') as f:
    for row in f:
        src_string += row.strip()

str_list = src_string.split(' ')
print(str_list)
