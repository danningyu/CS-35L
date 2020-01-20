a = 'this is a string'
print(a[0])
print(type(a))
print(a[-2]) #second to last char, equal to len(a)-2
print(len(a))

#slicing:
print(a[1:3]) #aka .substr
print(a[1:-1]) #from 1 to not incl. 1 from the end
print(a.find("string"))

test_list = ["element 1", "element 2", 2] #can mix elements
print(test_list[2]) # gives element at index 2
print(test_list[-1]) # negative works too
#items in lists are mutable
test_list.append("new item")
test_list.remove("new item") #only removes first occurrence
test_list.pop(1) #removes element at index 1, or if no number given, last one
print(test_list)

#split string into list:
s = "1,2,3,4"
print(s.split(',')) # split returns a list
#tuple: use ()
test_tuple = (1, 2.0, "test")
#elements are not mutable
#tuple is analogous to struct in C, while list is array

test_dict = {'key':'value'} #hash map: key-value pairs
# can't make a list a key because it's non hashable, but you can make a tuple a key
# dictionary doesn't have order so you can't access by index
# if you have a collision in a dictionary, it just overwrite the previous value
print(test_dict.keys()) #returns all keys
print(test_dict.values()) #returns all values
print(test_dict.items()) #returns key-value pairs as tuples

if True:
	print("anthing")
	if False:
		print("this won't get printed")
# be careful with identation!

if x and y or z:
	print("something")
elif x<y:
	print("test")
else:
	print("the else")

#use keyword in to check if item is element of list
a_list = [1, 2, 3, 4]
if 1 in a_list:
	print("1 is in the list")

d = {"1":"100", "2":"200"}
if "1" in d:
	print("1 in d")
	#thus, can check keys
	#cannot check values

for i in d.keys():
	print(i, d[i]) #print key-value pairs


for i in range(1, 20):
	#do something 20 times
range(1, 20, 2) #step by 2 every time, is 3rd paramter
#range(start, end, step)
#continue and break exist as well

range(a, b) #creates a list with range a to b-1: [a, b)

#while loop
while x==2:
	print('do soething')

# for loop:
for item in a_list: #for each loop

### functions ###
# def func_name(arg1, arg2):

def func_name(arg1, arg2):
	temp = arg1+arg2
	return temp

print(func_name(1, 2))

class className:
#variables are public by default
#to make private, add __
	publicvar = 5
	__privatevar = 2

	def __inti__(self, v):
		# like a constructor in C++
		self.var1 = v

	def function_name(self, arg1, arg2):
		#function inside class must always have a self argument
	temp = arg1 + arg2 + self.var1 #self needed for var1, like this
	return temp

t = className()
t2 = className(10) #will use our own __init__
t.function_name(1, 2)
prnt(t.function_name(1, 2))
#to access a __ var:
print(t._className__var2) #so not truly private!
# can do the same with a private function (if you make it __func_name)

#exception handling

try:
	print('some code here')
except TypeError
	print(errorname + 'occurreed')
finally:
	# do something regardless of try/except result

#try-except allows for program to continue even if there's an error
#useful for not letting program die

#else is also an option
