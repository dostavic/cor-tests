index = -22

# with open('../tst/SpectrumLoader_bin.cpp') as file:
#     # file_contents = file.read()
#     # print(file_contents)
#
#     while True:
#         # считываем строку
#         line = file.readline()
#         # прерываем цикл, если строка пустая
#         if not line:
#             break
#         # выводим строку
#         # print(line.strip())
#         file_contents = list(line)
#
#         for i in range(len(file_contents)):
#             if file_contents[i] == '[':
#                 print(file_contents[i])
#                 file_contents.insert(i + 1, str(index))
#                 index += 1
#         file.
#     # file_contents = list(line)
#     file.close()

    # with open('../tst/SpectrumLoader_bin.cpp', 'r') as file:
    #     lines = file.readlines()
    #
    # with open('../tst/SpectrumLoader_bin.cpp', 'w') as file:
    #     # lines = list(lines)
    #     list_lines = list(lines)
    #     for line in list_lines:
    #         for i in range(len(line)):
    #             if line[i] == '[':
    #
    #         file.write(new_line)

    # print(str(file_contents))
    # print(''.join(file_contents))

    # f = open('../tst/SpectrumLoader_bin.cpp', 'w')

    # for i in file_contents:
    #     f.write(i)
    # f.close()

with open('../tst/SpectrumLoader_bin.cpp', 'r') as file:
    with open('../tst/SpectrumLoader_bin1.cpp', 'w') as file_new:
        for line in file:
            new_line = line.replace('[]', f'[{str(index)}]')
            index += 1
            file_new.write(new_line)
            