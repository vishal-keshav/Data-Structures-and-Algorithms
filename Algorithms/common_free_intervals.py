# This question appeared in a youtube mock interview video.
# Link: https://www.youtube.com/watch?v=3Q_oYDQ2whs
# The guy, who has supposedly done thousands of 'project' and published them
# on his youtube channel, just blows up the whole interview session.
# He seems very confused when it comes to thinking clearly.

# So, I decided to give it a try(before I watched full interiview) and solved
# the problem in 20-25 minutes. Below is my solution.

class calender(object):
    def __init__(self):
        pass

    def solve(self, c1, b1, c2, b2, d):
        e1 = self.construct_free_slots(c1, b1)
        e2 = self.construct_free_slots(c2, b2)
        e = self.intersect_free_slots(e1, e2)
        e_refined = self.refine_slots(e, d)
        return e_refined

    def construct_free_slots(self, c, b):
        start = b[0]
        ret = []
        for slot in c:
            ret.append([start, slot[0]])
            start = slot[1]
        ret.append([start, b[1]])
        return ret

    def intersect_free_slots(self, e1, e2):
        i = 0
        j = 0
        ret = []
        while i<len(e1) and j<len(e2):
            interval = self.intersects(e1[i], e2[j])
            if len(interval)!=0:
                ret.append(interval)
            if e1[i][1] == e2[j][1]:
                i+=1
                j+=1
            elif self.compare(e1[i][1],e2[j][1]):
                i+=1
            elif not self.compare(e1[i][1],e2[j][1]):
                j+=1
        return ret

    def intersects(self, e1, e2):
        if self.compare(e1[0], e2[0]):
            left = e2[0]
        else:
            left = e1[0]
        if self.compare(e1[1], e2[1]):
            right = e1[1]
        else:
            right = e2[1]
        if self.compare(left, right):
            return [left, right]
        return []

    def refine_slots(self, e, d):
        ret = []
        for slot in e:
            if self.diff(slot[0], slot[1]) >= d:
                ret.append(slot)
        return ret

    def num(self, t):
        h,m = t.split(':')
        return int(h)*60 + int(m)

    def compare(self, t1, t2):
        t1 = self.num(t1)
        t2 = self.num(t2)
        return t1<t2

    def diff(self, t1, t2):
        return self.num(t2) - self.num(t1)
###################### END OF THE SOLUTION ####################################

def test():
    c1 = [['9:00', '10:30'], ['12:00', '13:00'], ['16:00', '18:00']]
    b1 = ['9:00', '20:00']

    #e1 = [[‘9:00’, ‘9:00’],[‘10:30’: ‘12:00’], [‘13:00’, ‘16:00’], [‘18:00’, ‘20:00’]]


    c2 = [['10:00', '11:30'], ['12:30', '14:30'], ['14:30', '15:00'], ['16:00', '17:00']]
    b2 = ['10:00', '18:30']

    #e2 = [[‘10:00’, ‘10:00’], [‘11:30’, ‘12:30’], [‘14:30’, ‘14:30’], [‘15:00’, ‘16:00’], [‘17:00’, ‘18:30’]]

    #e_1_2 = [[‘11:30’, ‘12:00’], [‘15:00’, ‘16:00’] , [‘18:00’, ‘18:30’]]

    d = 30

    solver = calender()
    result = solver.solve(c1,b1,c2,b2,d)
    print(result)

test()
