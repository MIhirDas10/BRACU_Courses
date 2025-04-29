# TASK 1

from OpenGL.GL import *  # Graphics library
from OpenGL.GLUT import *  # Utility tool
from OpenGL.GLU import *
import random

raindrop_coordinates1 = []
raindrop_coordinates2 = []
wind_speed = 0
r = g = b = 0 # black
t_r = t_g = t_b = 1 # white
changing = False
transition_speed = 0.002

# randomly generating x and y
for i in range(150):
    raindrop_coordinates1.append([random.randint(0, 1200), random.randint(0, 700)])
for i in range(100):
    raindrop_coordinates2.append([random.randint(0, 1200), random.randint(0, 700)])


def field():
    glBegin(GL_TRIANGLES)
    glColor3f(148/255, 95/255, 4/255)
    glVertex2f(0, 0)
    glVertex2f(0, 450)
    glVertex2f(1200, 0)

    glVertex2f(0, 450)
    glVertex2f(1200, 0)
    glVertex2f(1200, 450)
    glEnd()

def tree():
    glBegin(GL_TRIANGLES)
    for i in range(0, 1201, 80):
        # leaves part
        glColor3f(0, 0.7, 0)
        glVertex2f(i, 350)
        glVertex2f(i + 80, 350)
        glVertex2f(i + 40, 445)
        # trunk part
        glColor3f(125/255, 64/255, 0/255)
        glVertex2f(i + 35, 350)
        glVertex2f(i + 45, 350)
        glVertex2f(i + 40, 300)
    glEnd()

def house():
    glBegin(GL_QUADS)
    glColor3f(250/255, 241/255, 235/255)
    glVertex2f(400, 250)
    glVertex2f(400, 400)
    glVertex2f(800, 400)
    glVertex2f(800, 250)
    glEnd()

def door():
    glBegin(GL_QUADS)
    glColor3f(0.3, 0.2, 0.8)
    glVertex2f(570, 250)
    glVertex2f(570, 350)
    glVertex2f(630, 350)
    glVertex2f(630, 250)
    glEnd()

    glPointSize(6)
    glColor3f(0, 0, 0)
    glBegin(GL_POINTS)
    glVertex2f(615, 300)
    glEnd()

def windows():
    glColor3f(5/255, 103/255, 180/255)
    glBegin(GL_QUADS)
    # Left window
    glVertex2f(460, 300)
    glVertex2f(460, 350)
    glVertex2f(510, 350)
    glVertex2f(510, 300)
    glEnd()

    # lines
    glColor3f(0.1, 0.1, 0.1)
    glLineWidth(3)
    glBegin(GL_LINES)
    glVertex2f(460, 325)
    glVertex2f(510, 325)
    glEnd()

    glColor3f(0.1, 0.1, 0.1)
    glLineWidth(3)
    glBegin(GL_LINES)
    glVertex2f(485, 300)
    glVertex2f(485, 350)
    glEnd()
    # -----------------------------

    # Right window
    glColor3f(5/255, 103/255, 180/255)
    glBegin(GL_QUADS)
    glVertex2f(690, 300)
    glVertex2f(690, 350)
    glVertex2f(740, 350)
    glVertex2f(740, 300)
    glEnd()

    # lines
    glColor3f(0.1, 0.1, 0.1)
    glLineWidth(3)
    glBegin(GL_LINES)
    glVertex2f(690, 325)
    glVertex2f(740, 325)
    glEnd()

    glColor3f(0.1, 0.1, 0.1)
    glLineWidth(3)
    glBegin(GL_LINES)
    glVertex2f(715, 300)
    glVertex2f(715, 350)
    glEnd()
    # -----------------------------

def roof():
    glBegin(GL_TRIANGLES)
    glColor3f(0.7, 0.1, 0.1)
    glVertex2f(350, 390)
    glVertex2f(850, 390)
    glVertex2f(600, 500)
    glEnd()
    # extra
    glBegin(GL_QUADS)
    glColor3f(0.7, 0.1, 0.1)
    glVertex2f(705, 500)
    glVertex2f(705, 390)
    glVertex2f(745, 390)
    glVertex2f(745, 500)
    glEnd()

    glBegin(GL_QUADS)
    glColor3f(0.4, 0.4, 0.4)
    glVertex2f(700, 500)
    glVertex2f(700, 490)
    glVertex2f(750, 490)
    glVertex2f(750, 500)
    glEnd()


def border():
    glBegin(GL_QUADS)
    # glColor3f(59/255, 39/255, 25/255)
    glColor3f(74/255, 47/255, 30/255)
    glVertex2f(385, 238)
    glVertex2f(385, 250)
    glVertex2f(815, 250)
    glVertex2f(815, 238)
    glEnd()

def raindrops():
    glColor3f(0, 0.5, 1) # blue
    glLineWidth(1.3) # thickness
    glBegin(GL_LINES)
    
    for drop in raindrop_coordinates1:
        x, y = drop
        glVertex2f(x, y)
        glVertex2f(x-(wind_speed*3), y + 45) # 45 is adding length
    glEnd()

    glColor3f(0.5, 0.5, 0.5)  # grey
    glLineWidth(0.8)      # thickness
    glBegin(GL_LINES)

    for drop in raindrop_coordinates2:
        x, y = drop
        glVertex2f(x, y)
        glVertex2f(x-(wind_speed*3), y + 45)
    glEnd()

def animate():
    # for blue rain
    global raindrop_coordinates1, r, g, b, changing
    for i in range(len(raindrop_coordinates1)):
        x, y = raindrop_coordinates1[i] # (x, y)
        y -= 12  # speed
        x += wind_speed  # wind

        if y < 0: # reset
            y = 700 # height
            x = random.randint(0, 1200)
        raindrop_coordinates1[i] = (x % 1200, y)  # keeps it in boundary

    # grey rain
    global raindrop_coordinates2
    for i in range(len(raindrop_coordinates2)):
        x, y = raindrop_coordinates2[i]
        y -= 12  # speed
        x += wind_speed  # wind

        if y < 0:  # reset
            y = 700
            x = random.randint(0, 1200)
        raindrop_coordinates2[i] = (x % 1200, y)  # keeps it in boundary

    if changing == True:
        r = smooth_transition(r, t_r)
        g = smooth_transition(g, t_g)
        b = smooth_transition(b, t_b)
    glutPostRedisplay()

def smooth_transition(current, target):
    if current < target:
        return min(current + transition_speed, target) # day (0 -> 1)
    elif current > target:
        return max(current - transition_speed, target) # night (1 -> 0)
    return current

def key_control(key, x, y):
    global t_r, t_g, t_b, changing

    if key == b'd':  # day
        t_r = t_g = t_b = 1
        changing = True
    elif key == b'n':  # night
        t_r = t_g = t_b = 0
        changing = True

def special_keys(key, x, y):
    global wind_speed
    if key == GLUT_KEY_LEFT:
        wind_speed -= 1
    elif key == GLUT_KEY_RIGHT:
        wind_speed += 1
    # wind boundary
    if wind_speed > 10.0:
        wind_speed = 10.0
    elif wind_speed < -10.0:
        wind_speed = -10.0


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    glViewport(0, 0, 1200, 700)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0.0, 1200, 0.0, 700, 0.0, 1.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    
    glClearColor(r, g, b, 1.0)
    field()
    tree()
    house()
    door()
    windows()
    roof()
    raindrops()
    border()
    glutSwapBuffers()

glutInit()
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB)
glutInitWindowSize(1200, 700)
glutInitWindowPosition(400, 120)
wind = glutCreateWindow(b"22299480_MihirDas_task1_01.py")
glutDisplayFunc(display)
glutIdleFunc(animate)
glutKeyboardFunc(key_control)
glutSpecialFunc(special_keys)
glutMainLoop()









# # TASK 2


# import random
# from OpenGL.GL import *
# from OpenGL.GLUT import *
# from OpenGL.GLU import *

# balls = []
# blinking_mode = False
# freeze = False
# visible = True
# ball_size = 5
# speed = 1
# count = 0
# interval = 30

# def display():
#     global count, visible
#     count += 1

#     if blinking_mode:
#         if count % interval == 0:
#             visible = not visible  # toggle visible
#             print("toggle")

#     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
#     glViewport(0, 0, 500, 500)
#     glClearColor(0, 0, 0, 0)
#     glMatrixMode(GL_MODELVIEW)
#     glLoadIdentity()

#     if blinking_mode == False or visible == True:
#         for x, y, dir_x, dir_y, color in balls:
#             r, g, b = color
#             glColor3f(r, g, b)
#             glPointSize(ball_size)
#             glBegin(GL_POINTS)
#             glVertex2f(x, y)
#             glEnd()
#     glutSwapBuffers()

# def convert_coordinate(x, y): # flipping
#     return x, 500 - y

# def animate():
#     global balls
#     if freeze:
#         return

#     new_balls = []
#     for x, y, dir_x, dir_y, color in balls:
#         x += dir_x * speed
#         y += dir_y * speed
#         # bounce off walls
#         if x <= 0 or x >= 500:
#             dir_x *= -1  # direction -> reverse
#         if y <= 0 or y >= 500:
#             dir_y *= -1  # direction -> reverse
#         new_balls.append((x, y, dir_x, dir_y, color))
#     balls = new_balls
#     glutPostRedisplay()

# def mouseEvent(button, state, x, y):
#     global blinking_mode, visible
#     if freeze:
#         return
#     # new ball
#     gen_x, gen_y = convert_coordinate(x, y)
#     print(gen_x, gen_y)

#     if button == GLUT_LEFT_BUTTON:
#         if state == GLUT_DOWN:
#             blinking_mode = not blinking_mode  # toggle blinking mode
#             visible = True
#             glutPostRedisplay()

#     elif button == GLUT_RIGHT_BUTTON:
#         if state == GLUT_DOWN:
#             dir_x = random.choice([-1, 1])
#             dir_y = random.choice([-1, 1])
#             new_color = (random.random(), random.random(), random.random())
#             balls.append((gen_x, gen_y, dir_x, dir_y, new_color))

# def specialKeyEvent(key, x, y):
#     global speed
#     if freeze:
#         return
#     if key == GLUT_KEY_UP:
#         speed *= 1.5
#         # extra
#         if speed > 60:
#             speed = 60
#         print(speed)
#     elif key == GLUT_KEY_DOWN:
#         speed /= 1.5
#         # extra
#         if speed < 0.03:
#             speed = 0.03
#         print(speed)

# def keyboardEvent(key, x, y):
#     global freeze
#     if key == b' ':  # space button
#         freeze = not freeze  # toggle freeze 

# def init():
#     glClearColor(0, 0, 0, 0)
#     glMatrixMode(GL_PROJECTION)
#     glLoadIdentity()
#     gluOrtho2D(0, 500, 0, 500)
#     glMatrixMode(GL_MODELVIEW)

# glutInit()
# glutInitWindowSize(500, 500)
# glutInitWindowPosition(700, 250)
# glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB)
# glutCreateWindow(b"22299480_MihirDas_task2_01.py")
# init()
# glutDisplayFunc(display)
# glutIdleFunc(animate)
# glutKeyboardFunc(keyboardEvent)
# glutSpecialFunc(specialKeyEvent)
# glutMouseFunc(mouseEvent)
# glutMainLoop()
