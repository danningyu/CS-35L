# print("new string 1", end="")
# print("new string 2")

# import os

# os.func_name()

a = "this is a string"
# print(type(a))
# print(a[-1])
# print(a[len(a)-1])
# print(len(a))

# print(a[1:-1])

ret = a.find("string")
# print(ret)
# print(a.upper())

# test_list = ["element 1", "element b", 1.0, 5, [1,2]]
# # print(test_list[-1][0])
# print(test_list[1:3])
# print(len(test_list))
# test_list[0] = "element A"
# print(test_list)
# test_list.append("new through append")
# test_list.append("element A")
# test_list.remove('element A')
# print(test_list)
# test_list.pop(0)
# print(test_list)
# test_list.pop(-1)
# print(test_list)

# s = "one,two,three,4"
# print(s.split(','))


# test_tuple = (1,3.0,"test")
# test_tuple[2] = "new value"

# a = (1,2)
# test_dict = {"course name": "35L", "number": 36, "instructor": "prof. eggert", a: "234" }
# print(test_dict[a])
# test_dict['new key'] = "new value'"
# print(test_dict)
# test_dict['new key'] = [test_dict['new key'], "new value 2"]
# print(test_dict)
# print(test_dict.keys())
# print(test_dict.values())
# print(test_dict.items())
# d = {"1" : "100", "2": "200"}
# if "1" in d:
#   print("1 in d")
# # elif 2 in l:
# #   print("2 in l")
# else:
#   print("not in d")

# a = 0
# while a < 10:
#   print(a)
#   a += 2

l = [1, 2, 3, 4]
d = {"1" : "100", "2": "200"}
# for i in l:
#   print(i + 2)
# for i in d.keys():
#   print(i, d[i])

# a = 3
# b = 10
# for i in range(a, b, 2):
#   if i == 3:
#     continue
#   if i == 9:
#     break
#   print(i)



def func_name(arg1, arg2):
  if arg1 < 0:
    return 0
  tmp = arg1 + arg2
  return tmp

# print(func_name(1,2))



# class className:
#   __var2 = 5
#   def __init__(self, v):
#     self.var1 = v
#   def function_name(self, arg1, arg2):
#     if arg1 < 0:
#       return 0
#     tmp = arg1 + arg2 + self.var1
#     return tmp

# t = className(10)
# ret = t.function_name(1,2)
# print(ret)

# print(t._className__var2)


try:
  func_name(1,2,3)
except TypeError:
  print("error") 