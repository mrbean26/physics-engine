# Method of Projecting Vertices in 2D Combinations and Checking if Point is Within Face

# prequisites
class vec3:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

class vec2:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        return (self.x == other.x) and (self.y == other.y)

def sign(pointOne, pointTwo, PointThree):
    return (pointOne.x - PointThree.x) * (pointTwo.y - PointThree.y) - (pointTwo.x - PointThree.x) * (pointOne.y - PointThree.y)

def pointInTriangle(point, pointOne, pointTwo, pointThree):
    dOne = sign(point, pointOne, pointTwo)
    dTwo = sign(point, pointTwo, pointThree)
    dThree = sign(point, pointThree, pointOne)

    has_neg = (dOne < 0) or (dTwo < 0) or (dThree < 0)
    has_pos = (dOne > 0) or (dTwo > 0) or (dThree > 0)

    return not(has_neg and has_pos)

# test method
cubeVerticesFaces = [
    [vec3(1,-1,1), vec3(-1,-1,-1), vec3(1,-1,-1)],
    [vec3(-1,1,-1), vec3(0.999999,1,1), vec3(1,1,-0.999999)],
    [vec3(1,1,-0.999999), vec3(1,-1,1), vec3(1,-1,-1)],
    [vec3(0.999999,1,1), vec3(-1,-1,1), vec3(1,-1,1)],
    [vec3(-1,-1,1), vec3(-1,1,-1), vec3(-1,-1,-1)],
    [vec3(1,-1,-1), vec3(-1,1,-1), vec3(1,1,-0.999999)],
    [vec3(1,-1,1), vec3(-1,-1,1), vec3(-1,-1,-1)],
    [vec3(-1,1,-1), vec3(-1,1,1), vec3(0.999999,1,1)],
    [vec3(1,1,-0.999999), vec3(0.999999,1,1), vec3(1,-1,1)],
    [vec3(0.999999,1,1), vec3(-1,1,1), vec3(-1,-1,1)],
    [vec3(-1,-1,1), vec3(-1,1,1), vec3(-1,1,-1)],
    [vec3(1,-1,-1), vec3(-1,-1,-1), vec3(-1,1,-1)]
]

def pointInCube(point):
    global cubeVerticesFaces

    for i in range(len(cubeVerticesFaces)):
        currentPointCheck = vec2(point.x, point.y)
        pointOne = vec2(cubeVerticesFaces[i][0].x, cubeVerticesFaces[i][0].y)
        pointTwo = vec2(cubeVerticesFaces[i][1].x, cubeVerticesFaces[i][1].y)
        pointThree = vec2(cubeVerticesFaces[i][2].x, cubeVerticesFaces[i][2].y)

        if pointOne == pointTwo or pointOne == pointThree or pointTwo == pointThree:
            continue

        if(pointInTriangle(currentPointCheck, pointOne, pointTwo, pointThree)):

            for j in range(len(cubeVerticesFaces)):
                currentPointCheck = vec2(point.x, point.z)
                pointOne = vec2(cubeVerticesFaces[j][0].x, cubeVerticesFaces[j][0].z)
                pointTwo = vec2(cubeVerticesFaces[j][1].x, cubeVerticesFaces[j][1].z)
                pointThree = vec2(cubeVerticesFaces[j][2].x, cubeVerticesFaces[j][2].z)

                if pointOne == pointTwo or pointOne == pointThree or pointTwo == pointThree:
                    continue

                if(pointInTriangle(currentPointCheck, pointOne, pointTwo, pointThree)):

                    for k in range(len(cubeVerticesFaces)):
                        currentPointCheck = vec2(point.y, point.z)
                        pointOne = vec2(cubeVerticesFaces[k][0].y, cubeVerticesFaces[k][0].z)
                        pointTwo = vec2(cubeVerticesFaces[k][1].y, cubeVerticesFaces[k][1].z)
                        pointThree = vec2(cubeVerticesFaces[k][2].y, cubeVerticesFaces[k][2].z)

                        if pointOne == pointTwo or pointOne == pointThree or pointTwo == pointThree:
                            continue

                        if(pointInTriangle(currentPointCheck, pointOne, pointTwo, pointThree)):
                            
                            return True
    return False

#Works.good.
print(pointInCube(vec3(0, 0, 0)))
