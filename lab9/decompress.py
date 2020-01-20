import os, zlib

gitFilePath = '/u/ma/ugrad/danning/cslab/flow-test-dir/.git/'

gitBranch = open(gitFilePath+'/refs/heads/b1', 'r').read()
print(gitBranch)
objectPath = gitFilePath+'objects/'+gitBranch[0:2]+'/'+gitBranch[2:len(gitBranch)-1]
print(objectPath)

gitObject = open(objectPath, 'rb').read()
decObject = zlib.decompress(gitObject).decode('utf-8')
# decObject = zlib.decompress(gitObject)
# decObject = zlib.decompress(gitObject)
# decObject = zlib.decompress('/u/ma/ugrad/danning/cslab/flow-test-dir/.git/refs/heads/b1')
print(decObject)