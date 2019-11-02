# This file solves problem 127 that appeared in leet code
# Link: https://leetcode.com/problems/word-ladder/

class Solution(object):
    def distance(self,w1, w2):
        d = 0
        for i in range(len(w1)):
            if w1[i]!=w2[i]:
                d+=1
        return d

    def get_all_words(self, word):
        n = len(word)
        res = []
        for i in range(n):
            new_word = word[0:i] + "_" + word[i+1:]
            res.append(new_word)
        return res

    class Graph(object):
        class vertex(object):
            def __init__(self, key):
                self.key = key
                self.neighbour = []

            def add_neighbour(self, v):
                if v not in self.neighbour:
                    self.neighbour.append(v)

        def __init__(self):
            self.vertices = {}

        def add_vertex(self, key):
            self.vertices[key] = self.vertex(key)

        def add_edge(self, v1, v2):
            self.vertices[v1].add_neighbour(v2)
            self.vertices[v2].add_neighbour(v1)

    def build_graph(self,wordList):
        #(This one gives TLE)
        g = self.Graph()
        for i,word in enumerate(wordList):
            g.add_vertex(i)
        for i in range(len(wordList)):
            for j in range(i+1,len(wordList)):
                if i==j:
                    continue
                if self.distance(wordList[i], wordList[j]) == 1:
                    g.add_edge(i,j)
        return g

    def build_graph_fast(self,wordList):
        g = self.Graph()
        for i,word in enumerate(wordList):
            g.add_vertex(i)
        # Build the word to indexes mapping first in O(n*k) time
        word_to_index = {}
        for i,word in enumerate(wordList):
            word_types = self.get_all_words(word)
            for word_type in word_types:
                if word_type not in word_to_index:
                    word_to_index[word_type] = [i]
                else:
                    word_to_index[word_type].append(i)
        # Now iterate over words again and build the graph
        for i,word in enumerate(wordList):
            word_types = self.get_all_words(word)
            for word_type in word_types:
                indexes = word_to_index[word_type]
                for j in indexes:
                    if j!=i:
                        g.add_edge(i,j)
        return g

    def bfs(self, g, s):
        # First assign each vertex in the graph a color
        for v in g.vertices.values():
            v.color = "white"
            v.dist = 0
        # Second assing the source a distance of 0, and a color of gray
        g.vertices[s].dist = 1
        g.vertices[s].color = "grey"
        # Make a queue and pop untill its empty
        Q = [s]
        while len(Q)>0:
            u = Q.pop(0)
            g.vertices[u].color = "black"
            V = g.vertices[u].neighbour
            for v in V:
                if g.vertices[v].color == "white":
                    g.vertices[v].color = "grey"
                    g.vertices[v].dist = g.vertices[u].dist + 1
                    Q.append(v)
        return g


    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        # Solved in 35 minutes
        if endWord not in wordList:
            return 0
        if beginWord not in wordList:
            wordList.append(beginWord)
        g = self.build_graph_fast(wordList)
        #print(wordList)
        #for v in g.vertices.values():
        #    print(v.key, v.neighbour)
        g_ = self.bfs(g, wordList.index(beginWord))
        return g_.vertices[wordList.index(endWord)].dist


def main():
    beginWord = "hit"
    endWord = "cog"
    wordList = ["hot","dot","dog","lot","log","cog"]
    sol = Solution()
    # Expected output = 5
    print(sol.ladderLength(beginWord, endWord, wordList))

main()
