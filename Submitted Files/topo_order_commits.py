#!/usr/local/cs/bin/python3

# Danning Yu, 305087992
# CS 35L Assignment 9
# To do: fix mixing of snake case and camel case

import os, sys, zlib

# Class definition for CommitNode
class CommitNode:
    def __init__(self, commit_hash):
        """
        :type commit_hash: str
        """
        self.commit_hash = commit_hash
        #set of parent hashes, NOT CommitNodes
        self.parents = set() 
        self.children = set()
        self.status = 0

    def __repr__(self):
        return "Commit hash: %s\nParents: %s\nChildren:%s\n" \
        %(self.commit_hash, sorted(self.parents), sorted(self.children))

    def __str__(self):
        return "Commit hash: %s\nParents: %s\nChildren:%s\n" \
        %(self.commit_hash, sorted(self.parents), sorted(self.children))
#End class definition for CommitNode

#Helper Functions
def get_parent_hashes(commit_msg):
    lines = commit_msg.splitlines()
    parent_hashes = set()
    for line in lines:
        if line.find("author") != -1:
           break
        if line.find("parent") != -1:
            parent_hashes.add(line[-40:])
    return parent_hashes

def get_decomp_object(hash_val, objectDirectory):
    hashFilePath = objectDirectory+hash_val[0:2]+'/'+hash_val[2:]
    gitObject = open(hashFilePath, 'rb').read()
    decObject = zlib.decompress(gitObject).decode('utf-8')
    return decObject

def all_children_visited(node, nodeDict):
    all_visited = True
    for child_hash in node.children:
        if nodeDict[child_hash].status != 2:
            return False;
    return True;

def get_topo_order():
    ##### Step 1 #####
    gitFound = False;
    path = os.getcwd()

    while path != '' and not gitFound:
        for (root, dirs, files) in os.walk(path, topdown=True): 
            for dir in dirs:
                # print(dir)
                if(dir == '.git'):
                    gitFound = True;
                    break    
            break
        if gitFound:
            break
        path = path[0:path.rfind('/')]
        # gets rid of current level and the /

    if not gitFound:
        print('Not inside a Git repository')
        sys.exit(1)

    #####  END Step 1  #####
    ##### START Step 2 and 3 #####
    # First get the hashes of all the branches (in reality,
    #     the final children commits)
    # Then for each hash, decompress the object and keep going
    #     until there's no more parent (hit root node)
    # Every time, add the node to a dictionary, where hash
    #     is key and commitnode is value

    branchPaths = []
    branchHashes = {}
    branchDirectory = path+"/.git/refs/heads/"
    objectDirectory = path+"/.git/objects/"
    nodeDict = {}

    for (root, dirs, files) in os.walk(branchDirectory, topdown=True): 
            files = [file for file in files if not file[0] == '.']
            dirs[:] = [direc for direc in dirs if not direc[0] == '.']
            for file in files:
                branchHash = open(os.path.join(root, file), 'r').read()[:-1]
                if branchHashes.get(branchHash) is not None:
                    branchHashes[branchHash].append(file)
                else:
                    branchHashes[branchHash] = [file]

    for branchHash in branchHashes.keys():
        if nodeDict.get(branchHash) is None:
            branchNode = CommitNode(branchHash)
            parent_hashes = get_parent_hashes(get_decomp_object(branchHash, objectDirectory))
            nodeDict[branchHash] = branchNode
            branchNode.parents = branchNode.parents | parent_hashes #union of sets
            node_stack = []
            node_stack.append(branchNode)
            while node_stack:
                currNode = node_stack.pop()
                for parentHash in currNode.parents:
                    parentNode = None;
                    if nodeDict.get(parentHash) is not None:
                        # already exists, so parents have already been added
                        # just need to update children
                        parentNode = nodeDict[parentHash]
                        parentNode.children.add(currNode.commit_hash)
                        continue;
                    else:
                        #make a new node, add its parents and children
                        # add to dictionary, and then push to node_stack
                        parentNode = CommitNode(parentHash)
                        parentNode.parents = get_parent_hashes(get_decomp_object(parentHash, objectDirectory))
                        parentNode.children.add(currNode.commit_hash)
                        nodeDict[parentHash] = parentNode
                        node_stack.append(parentNode)

    ##### END Step 2 and 3 #####
    ##### START Step 4 and 5 #####

    root_commits = [] #starting points for a DFS search
    for node in nodeDict.values():
        if not node.parents:
            root_commits.append(node)

    dfs_stack = []
    printed_something = False
    last_printed_node = None;
    for root_node in root_commits:
        dfs_stack.append(root_node)
        root_node.status = 1;
        last_stick = False;
        while dfs_stack:
            currNode = dfs_stack[-1]
            if not currNode.children or all_children_visited(currNode, nodeDict): 
            #has no children (hashes) or all of its children have be visited
                
                #printing the children of the first commit
                if last_stick:
                    print("=", end="")
                    first = True;
                    for child_hash in currNode.children:
                        if first:
                            print(child_hash, end="")
                            first = False;
                        else:
                            print(" " + child_hash, end = "")
                    print("\n", end = "")
                    last_stick = False;

                #print the hash of current node
                print(currNode.commit_hash, end = "")
                printed_something = True;

                #immediately after, print its associated branches
                if branchHashes.get(currNode.commit_hash) is not None:
                    for branch_name in sorted(branchHashes[currNode.commit_hash]):
                        print(" " +branch_name, end = "")
                print("")
                currNode.status = 2 #DONE_VISITING
                last_visited_node = currNode
                dfs_stack.pop()
                continue

            #no more childless nodes, so time to look down another path
            if currNode.status == 1 and len(currNode.children) > 1 and printed_something:
                first = True;
                for parentHash in sorted(last_visited_node.parents):
                    if first:
                        print(parentHash, end = "")
                        first = False;
                    else:
                        print(" " + parentHash, end="")
                print("=\n\n", end = "")
                last_stick = True;

            for child_hash in sorted(currNode.children, reverse=True):
                #find the first child whose path we haven't gone down yet
                if nodeDict[child_hash].status == 0:
                    currNode.status = 1 #CURR_VISITING
                    dfs_stack.append(nodeDict[child_hash])
                    break

if __name__ == '__main__':
    get_topo_order()