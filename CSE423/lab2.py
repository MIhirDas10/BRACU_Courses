from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import random, time

WIDTH, HEIGHT = 500, 800
TOP_AREA = 720
diamond_x, diamond_y = 250, TOP_AREA
diamond_size = 30
speed, increasing_rate = 100, 4
diamond_color = (1.0, 1.0, 1.0)
catcher_x, catcher_y = 250, 50 # position
catcher_width, catcher_height, catcher_speed = 100, 20, 10

score, high_score = 0, 0
last_time = time.time()
game_active = True
game_paused = False
# position
buttons = {
    "restart": {"x": 50, "y": 760, "size": 30, "color": (0, 1, 1)},
    "toggle":  {"x": 250, "y": 760, "size": 30, "color": (1, 0.6, 0)},
    "stop":    {"x": 450, "y": 760, "size": 30, "color": (1, 0, 0)}
}

def draw_point(x, y):
    glBegin(GL_POINTS)
    glVertex2i(int(x), int(y))
    glEnd()
# finding zone
def find_zone(x0, y0, x1, y1):
    dx, dy = x1 - x0, y1 - y0
    if abs(dx) >= abs(dy):
        if dx >= 0 and dy >= 0: return 0
        if dx < 0 and dy >= 0: return 3
        if dx < 0 and dy < 0: return 4
        else: return 7
    else:
        if dx >= 0 and dy > 0: return 1
        if dx < 0 and dy > 0: return 2
        if dx < 0 and dy <= 0: return 5
        else: return 6
# converting to zone 0
def convert_to_zone0(zone, x, y):
    if zone == 0: return x, y
    if zone == 1: return y, x
    if zone == 2: return y, -x
    if zone == 3: return -x, y
    if zone == 4: return -x, -y
    if zone == 5: return -y, -x
    if zone == 6: return -y, x
    return x, -y
# converting back into the original zone
def convert_back_to_original(zone, x, y):
    return convert_to_zone0(zone, x, y)
# Mid Point Line function
def MPL(x0, y0, x1, y1, zone):
    dx, dy = x1 - x0, y1 - y0
    d, dir_E, dir_NE = 2*dy-dx, 2*dy, 2*(dy-dx)
    x, y = x0, y0
    while x <= x1:
        conv_x, conv_y = convert_back_to_original(zone, x, y)
        draw_point(conv_x, conv_y)
        if d > 0:
            y += 1
            x += 1
            d += dir_NE
        else:
            d += dir_E
            x += 1
# eight way symmetry
def EWS(x0, y0, x1, y1):
    # find zone
    # convert the x0, y0, x1, y1 into zone 0
    zone = find_zone(x0, y0, x1, y1)
    x0_z0, y0_z0 = convert_to_zone0(zone, x0, y0)
    x1_z0, y1_z0 = convert_to_zone0(zone, x1, y1)
    MPL(x0_z0, y0_z0, x1_z0, y1_z0, zone)

def draw_diamond(cx, cy, size, color):
    glColor3f(color[0], color[1], color[2])  # r, g, b
    half = size // 2 # to make the diamond a little smaller
    EWS(cx, cy + half, cx + half, cy) # right-top
    EWS(cx + half, cy, cx, cy - half) # right-bottom
    EWS(cx, cy - half, cx - half, cy) # left-bottom
    EWS(cx - half, cy, cx, cy + half) # left-top

def draw_catcher(cx, cy, w, h, color):
    glColor3f(color[0], color[1], color[2])  # r, g, b
    # print("this is ", cx, cy, w, h)

    EWS(cx-w//2, cy, cx-w//4, cy-h)     # left
    EWS(cx-w//4, cy-h, cx+w//4, cy-h)   # bottom
    EWS(cx+w//4, cy-h, cx+w//2, cy)     # right
    EWS(cx-w//2, cy, cx+w//2, cy)       # top

def draw_icon(x, y, size, icon):
    if icon == "restart":
        # x -> 50
        EWS(x-size//3, y, x, y+size//3) # left-top (40, 720, 50, 730)
        EWS(x, y-size//3, x-size//3, y) # left-bottom (50, 710, 40, 720)
        EWS(x-size//3, y, x+size//2, y) # mid (40, 720, 70, 720)

    elif icon == "toggle":
        if game_paused:
            EWS(x - size//3, y - size//3, x - size//3, y + size//3) # left
            EWS(x + size//3, y - size//3, x + size//3, y + size//3) # right
            EWS(x - size//3, y + size//3, x + size//3, y + size//3) # top
            EWS(x - size//3, y - size//3, x + size//3, y - size//3) # bottom
        else:
            EWS(x - size//3, y - size//3, x - size//3, y + size//3)
            EWS(x + size//3, y - size//3, x + size//3, y + size//3)

    elif icon == "stop":
        EWS(x-size/3, y-size/3, x+size/3, y+size/3)
        EWS(x-size/3, y+size/3, x+size/3, y-size/3)

def draw_all_buttons():
    for name in buttons:
        # extracting info
        btn = buttons[name]
        # print(btn)
        color = btn["color"]
        x = btn["x"]
        y = btn["y"]
        size = btn["size"]
        glColor3f(color[0], color[1], color[2])
        draw_icon(x, y, size, name)

def detect_collision():
    # --- diamond boundary ---
    diamond_left = diamond_x - diamond_size // 2
    diamond_right = diamond_x + diamond_size // 2
    diamond_top = diamond_y + diamond_size // 2
    diamond_bottom = diamond_y - diamond_size // 2
    # print("diamond",diamond_left, diamond_right, diamond_top, diamond_bottom)

    # --- catcher boundary ---
    catcher_left = catcher_x - catcher_width // 2
    catcher_right = catcher_x + catcher_width // 2
    catcher_top = catcher_y + catcher_height // 2
    catcher_bottom = catcher_y - catcher_height // 2
    # print("catcher",catcher_left, catcher_right, catcher_top, catcher_bottom)
    
    # collision happens -> returns True
    return (diamond_left < catcher_right and
            diamond_right > catcher_left and
            diamond_bottom < catcher_top and 
            diamond_top > catcher_bottom)

def create_new_diamond():
    global diamond_x, diamond_y, diamond_color
    diamond_y = TOP_AREA
    diamond_x = random.randint(diamond_size, WIDTH - diamond_size)
    r, g, b = random.random(), random.random(), random.random()
    if max(r, g, b) < 0.3:
        r, g, b = 255/256, 228/256, 153/256
        # print("yes!")
    diamond_color = (r, g, b)
    # print(diamond_color)

def restart_game():
    global catcher_x, score, speed, game_active, game_paused, last_time
    catcher_x = WIDTH//2
    score, speed = 0, 100
    game_active = True
    game_paused = False
    last_time = time.time()
    create_new_diamond()
    print("Starting Over")

def end_game():
    global high_score, game_active
    game_active = False # game over
    if score > high_score:
        high_score = score
        print(f"New High Score: {high_score}")
    print(f"Game Over! Final Score: {score}")

def update_game(_):
    global diamond_y, speed, last_time, score
    if game_active and not game_paused:
        present = time.time()
        # how much time has passed since the last frame
        dt = present - last_time
        last_time = present
        diamond_y -= speed * dt
        speed += increasing_rate * dt
        if detect_collision():
            score += 1
            glColor3f(0,1,0)
            print("Score:", score)
            create_new_diamond()
            glColor3f(1,1,1)
        elif diamond_y - diamond_size/2 < 0:
            end_game()
            
    glutPostRedisplay() # this iterates over again and again
    glutTimerFunc(16, update_game, 0) 

def handle_keyboard(key, x, y):
    global catcher_x, last_time, game_paused
    # extra -> space key for pausing
    if key == b' ':
        game_paused = not game_paused
        if not game_paused:
            last_time = time.time()
def keyboardEvent(key, x, y):
    global catcher_x
    if not game_active or game_paused:
        return
    # Move catcher with arrow keys
    if key == GLUT_KEY_LEFT:
        catcher_x -= catcher_speed
    elif key == GLUT_KEY_RIGHT:
        catcher_x += catcher_speed

    # Keep catcher inside screen
    if catcher_x < catcher_width // 2:
        catcher_x = catcher_width // 2
    elif catcher_x > WIDTH - catcher_width // 2:
        catcher_x = WIDTH - catcher_width // 2
        glutPostRedisplay()

def mouseEvent(button, state, x, y):
    print(x, y)
    if button != GLUT_LEFT_BUTTON or state != GLUT_DOWN: return None
    else:
        y = HEIGHT - y # flipping
        # print(y)
        for name, btn in buttons.items():
            # extracting the x, y coordinates and size of the buttons
            button_x = btn["x"]
            button_y = btn["y"]
            button_size = btn["size"]
            # button boundaries
            left = button_x - button_size//2
            right = button_x + button_size//2
            top = button_y + button_size//2
            bottom = button_y - button_size//2
            # print(left, right)
            # print(top, bottom)
            # checking if click is inside of button boundary
            if left <= x <= right and bottom <= y <= top:
                clicking(name) # passes the button name

def clicking(name):
    global last_time, game_paused
    if name == "restart":
        restart_game()
    elif name == "toggle":
        game_paused = not game_paused
        if not game_paused:
            last_time = time.time() # sets the time to the present time
    elif name == "stop":
        print("Goodbye! Final Score:", score)
        glutLeaveMainLoop() # exit OpenGL program

# EXTRA STUFF ------------------
def draw_score():
    glColor3f(1, 1, 1) # white
    glRasterPos2i(10, 10) # width and height
    text1 = f"Score: {score}"
    text2 = f"                               High Score: {high_score}"
    for c in text1:
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ord(c))
    for c in text2:
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ord(c))
# ------------------------------

def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    if not game_active: # game over/ended
        color = (1, 0, 0) # red
    else: # still going
        color = (1, 1, 1) # white
    draw_catcher(catcher_x, catcher_y, catcher_width, catcher_height, color)

    if game_active:
        draw_diamond(int(diamond_x), int(diamond_y), diamond_size, diamond_color)
    draw_all_buttons()
    draw_score()
    glutSwapBuffers()

def init():
    glClearColor(0, 0, 0, 0)
    glPointSize(2)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluOrtho2D(0, WIDTH, 0, HEIGHT)
    glMatrixMode(GL_MODELVIEW)
    create_new_diamond()

glutInit()
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB)
glutInitWindowSize(WIDTH, HEIGHT)
glutInitWindowPosition(700, 100)
glutCreateWindow(b"22299480_lab2")
init()
glutDisplayFunc(display)
glutKeyboardFunc(handle_keyboard)
glutSpecialFunc(keyboardEvent)
glutMouseFunc(mouseEvent)
glutTimerFunc(0, update_game, 0)
glutMainLoop()