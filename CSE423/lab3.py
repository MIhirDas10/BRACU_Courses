from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import random
import math

hide_player_head = False
# cheat mode variables
cheat_mode = False
gun_pov = False
cheat_rotation_speed = 3
target_pos = (0, 0, 0)
up_vector = (0, 0, 1)
first_person_view = False

top_view_mode = False
over_view_mode = False
player_coordinate = [300, 300, 30]
p_angle = 0
lifes = 5
score = 0
bullets_missed = 0
game_over = False

cam_coordinates = [300, 500, 350]
fovY = 120
MAX_ENEMIES = 5
enemies = []
GRID_LENGTH = 600
enemy_speed = .1
enemy_size_factor = 1.0
enemy_size_increasing = True
enemy_size_change_rate = 0.01
bullets = []
bullet_speed = 10

def enemy_spawn():
    global enemies
    enemies = []
    for i in range(MAX_ENEMIES):
        x = random.randint(50, GRID_LENGTH - 50)
        y = random.randint(50, GRID_LENGTH - 50)
        enemies.append([x, y, 30])

def respawn_enemy(enemy_index):
    x = random.randint(50, GRID_LENGTH - 50)
    y = random.randint(50, GRID_LENGTH - 50)
    while abs(x - player_coordinate[0]) < 100 and abs(y - player_coordinate[1]) < 100:
        x = random.randint(50, GRID_LENGTH - 50)
        y = random.randint(50, GRID_LENGTH - 50)
    enemies[enemy_index] = [x, y, 30]
    
def update_enemies():
    global enemies, lifes, enemy_size_factor,enemy_size_increasing
    # enemy effect
    if enemy_size_increasing:
        enemy_size_factor += enemy_size_change_rate
        if enemy_size_factor >= 1.2:
            enemy_size_increasing = False
    else:
        enemy_size_factor -= enemy_size_change_rate
        if enemy_size_factor <= 0.8:
            enemy_size_increasing = True
    # -----------------------
    for i, enemy in enumerate(enemies):
        dx, dy = player_coordinate[0]-enemy[0], player_coordinate[1]-enemy[1]
        dist = math.sqrt(dx**2 + dy**2)

        if dist > 0:
            enemy[0] += (dx/dist) * enemy_speed
            enemy[1] += (dy/dist) * enemy_speed

            if dist < 60:
                lifes -= 1
                respawn_enemy(i)
                if lifes <= 0:
                    game_is_over()

def draw_text(x, y, text, font=GLUT_BITMAP_HELVETICA_18):
    glColor3f(1,1,1)
    glMatrixMode(GL_PROJECTION)
    glPushMatrix()
    glLoadIdentity()
    gluOrtho2D(0, 1000, 0, 800)  # left, right, bottom, top
    glMatrixMode(GL_MODELVIEW)
    glPushMatrix()
    glLoadIdentity()
    glRasterPos2f(x, y)
    for ch in text:
        glutBitmapCharacter(font, ord(ch))
    glPopMatrix()
    glMatrixMode(GL_PROJECTION)
    glPopMatrix()
    glMatrixMode(GL_MODELVIEW)

# ------------------------------------------------------------
def game_is_over():
    global game_over
    game_over = True
# --------------------------- RESET --------------------------
def reset_game():
    global player_coordinate, p_angle, lifes, score, bullets_missed, game_over, bullets, cheat_mode, gun_pov

    player_coordinate = [300, 300, 30]
    p_angle = 0
    lifes = 5
    score = 0
    bullets_missed = 0
    game_over = False
    bullets = []
    cheat_mode = False
    gun_pov = False
    enemy_spawn()
    print('Game Reseted')
# --------------------------- RESET --------------------------
# --------------------------- PLAYER -------------------------
def draw_player():
    glPushMatrix()
    glTranslatef(player_coordinate[0], player_coordinate[1], player_coordinate[2])
    if game_over:
        glRotatef(270, 0, 1, 0)
    else:
        glRotatef(p_angle, 0, 0, 1)
    #body
    glTranslatef(-3, 0, 10 )
    glScalef(.7,.7,1.4)
    glColor3f(0.2, 0.5, 0.2)  
    glutSolidCube(40)
    #head
    if not hide_player_head:
        glPushMatrix()
        glTranslatef(0, 0, 30)
        glColor3f(0, 0, 0)
        gluSphere(gluNewQuadric(), 12, 15, 15)
        glPopMatrix()
    #hands
    glPushMatrix()
    glTranslatef(10, 15, 0)
    glRotatef(90, 0, 1, 0)
    glColor3f(.93, 0.68, 0.53)  
    gluCylinder(gluNewQuadric(), 10, 2, 30, 10, 10)
    glPopMatrix()
    glPushMatrix()
    glTranslatef(10, -15, 0)
    glRotatef(90, 0, 1, 0)
    glColor3f(.93, 0.68, 0.53)  
    gluCylinder(gluNewQuadric(), 10, 2, 30, 10, 10)
    glPopMatrix()
    # Left leg
    glPushMatrix()
    glTranslatef(0, 15, -10)
    glColor3f(0, 0, 1)  
    glRotatef(180, 0, 1, 0) 
    gluCylinder(gluNewQuadric(), 10, 3, 30, 10, 10)
    glPopMatrix()
    # Right leg
    glPushMatrix()
    glTranslatef(0, -15, -10)
    glColor3f(0, 0, 1)  
    glRotatef(180, 0, 1, 0) 
    gluCylinder(gluNewQuadric(), 10, 3, 30, 10, 10)
    glPopMatrix()
    #gun 
    glPushMatrix()
    glTranslatef(10, 0, 0)
    glRotatef(90, 0, 1, 0)
    glColor3f(0.3, 0.3, 0.3) 
    gluCylinder(gluNewQuadric(), 10, 6, 50, 15, 10)
    glPopMatrix()
    glPopMatrix()
# --------------------------- PLAYER -------------------------
# --------------------------- ENEMY --------------------------
def draw_enemies():
    for enemy in enemies:
        glPushMatrix()
        glTranslatef(enemy[0], enemy[1], enemy[2])
        # Draw main enemy body (red sphere)
        glColor3f(1, 0, 0)  # Red
        gluSphere(gluNewQuadric(), 25 * enemy_size_factor, 20, 20)
        # Draw enemy eye (black sphere)
        glTranslatef(0, 0, 30 * enemy_size_factor)
        glColor3f(0, 0, 0)  # Black
        gluSphere(gluNewQuadric(), 12 * enemy_size_factor, 15, 15)
        glPopMatrix()
# --------------------------- ENEMY --------------------------
# --------------------------- BULLETS ------------------------
def fire_bullet():
    if game_over:
        return None

    angle_rad = math.radians(p_angle)
    dx = math.cos(angle_rad)
    dy = math.sin(angle_rad)
    gun_length = 10
    start_x = player_coordinate[0] + dx * gun_length
    start_y = player_coordinate[1] + dy * gun_length
    start_z = player_coordinate[2] + 10 
    bullets.append([start_x, start_y, start_z, dx, dy])

def draw_bullets():
    for bullet in bullets:
        glPushMatrix()
        glTranslatef(bullet[0], bullet[1], bullet[2])
        glColor3f(1, 0, 0)  
        glutSolidCube(8)
        glPopMatrix()

def has_collided_3d(x1, y1, z1, w1, h1, d1, x2, y2, z2, w2, h2, d2):
    return (x1 < x2 + w2 and x1 + w1 > x2 and
            y1 < y2 + h2 and y1 + h1 > y2 and
            z1 < z2 + d2 and z1 + d1 > z2)

def check_bullet_enemy_collision(bullet, enemy):
    bullet_width = 10
    bullet_height = 10
    bullet_depth = 10
    bullet_x = bullet[0] - bullet_width/2
    bullet_y = bullet[1] - bullet_height/2
    bullet_z = bullet[2] - bullet_depth/2

    enemy_width = 60
    enemy_height = 60
    enemy_depth = 60
    enemy_x = enemy[0] - enemy_width/2
    enemy_y = enemy[1] - enemy_height/2
    enemy_z = enemy[2] - enemy_depth/2
    
    return has_collided_3d(bullet_x, bullet_y, bullet_z, bullet_width, bullet_height, bullet_depth,
                           enemy_x, enemy_y, enemy_z, enemy_width, enemy_height, enemy_depth)

def update_bullets():
    global bullets, enemies, score, bullets_missed
    remove_bullets = []
    if bullets_missed >= 10:
        game_is_over()

    for i, bullet in enumerate(bullets):
        bullet[0] += bullet[3] * bullet_speed
        bullet[1] += bullet[4] * bullet_speed
        hit = False
        for j, enemy in enumerate(enemies):
            bullet_width = 10
            bullet_height = 10
            bullet_x = bullet[0] - bullet_width/2
            bullet_y = bullet[1] - bullet_height/2
            enemy_width = 60
            enemy_height = 60
            enemy_x = enemy[0] - enemy_width/2
            enemy_y = enemy[1] - enemy_height/2

            if check_bullet_enemy_collision(bullet, enemy):
                hit = True
                respawn_enemy(j)
                score += 1
                break

        if (bullet[0] < 0 or bullet[0] > GRID_LENGTH or
            bullet[1] < 0 or bullet[1] > GRID_LENGTH or hit):
            remove_bullets.append(i)
            if not hit:
                bullets_missed += 1

    for i in sorted(remove_bullets, reverse=True):
        if i < len(bullets):
            bullets.pop(i)
# --------------------------- BULLETS ------------------------
# ---------------------------- GRID --------------------------
def draw_grid():
    grid_size = GRID_LENGTH
    cell_size = grid_size/13
    wall_height = 100
    glBegin(GL_QUADS)
    for i in range(13): # 13*13
        for j in range(13):
            x1 = i * cell_size
            y1 = j * cell_size
            x2 = (i+1) * cell_size
            y2 = (j+1) * cell_size
            if (i+j)%2 == 0:
                glColor3f(1.0, 1.0, 1.0) 
            else:
                glColor3f(0.7, 0.5, 0.95)  #purple
            glVertex3f(x1, y1, 0)
            glVertex3f(x2, y1, 0)
            glVertex3f(x2, y2, 0)
            glVertex3f(x1, y2, 0)
    glEnd()
# ---------------------------- GRID --------------------------
# ---------------------------- BOUNDARY ----------------------------
def wall():
    grid_size = GRID_LENGTH
    cell_size = grid_size/13
    wall_height = 100
    # cyan wall
    glBegin(GL_QUADS)
    glColor3f(0, 1, 1)
    glVertex3f(0, grid_size, 0)
    glVertex3f(grid_size, grid_size, 0)
    glVertex3f(grid_size, grid_size, wall_height)
    glVertex3f(0, grid_size, wall_height)
    glEnd()
    # yellow wall
    glBegin(GL_QUADS)
    glColor3f(1, 1, 0) 
    glVertex3f(0, 0, 0)
    glVertex3f(grid_size, 0, 0)
    glVertex3f(grid_size, 0, wall_height)
    glVertex3f(0, 0, wall_height)
    glEnd()
    # blue wall (right)
    glColor3f(0, 0, 1) 
    glBegin(GL_QUADS)
    glVertex3f(grid_size, 0, 0)
    glVertex3f(grid_size, grid_size, 0)
    glVertex3f(grid_size, grid_size, wall_height)
    glVertex3f(grid_size, 0, wall_height)
    glEnd()
    # green wall (left)
    glColor3f(0, 1, 0)
    glBegin(GL_QUADS)
    glVertex3f(0, 0, 0)
    glVertex3f(0, grid_size, 0)
    glVertex3f(0, grid_size, wall_height)
    glVertex3f(0, 0, wall_height)
    glEnd()
# ---------------------------- BOUNDARY ----------------------------
def keyboardListener(key, x, y):
    global player_coordinate, p_angle, cheat_mode, gun_pov
    move_speed = 10
    rotation_speed = 5

    # forward (w key)
    if key == b'w':  
        # angle_rad = math.radians(p_angle)
        # dx = move_speed * math.cos(angle_rad)
        # dy = move_speed * math.sin(angle_rad)
        # new_x = player_coordinate[0] + dx
        # new_y = player_coordinate[1] + dy
        # if 30 < new_x < GRID_LENGTH - 30 and 30 < new_y < GRID_LENGTH - 30:
        #     player_coordinate[0] = new_x
        #     player_coordinate[1] = new_y

        player_coordinate[0] += 5
        player_coordinate[1] += 5

    # backward (s key)
    if key == b's' and not game_over:
        angle_rad = math.radians(p_angle)
        dx = move_speed * math.cos(angle_rad)
        dy = move_speed * math.sin(angle_rad)
        new_x = player_coordinate[0] - dx
        new_y = player_coordinate[1] - dy
        if 30 < new_x < GRID_LENGTH - 30 and 30 < new_y < GRID_LENGTH - 30:
            player_coordinate[0] = new_x
            player_coordinate[1] = new_y

    # rotate left (a key)
    if key == b'a' and not game_over and not cheat_mode:
        p_angle = (p_angle + rotation_speed) % 360
    # rotate right (d key)
    if key == b'd' and not game_over and not cheat_mode:
        p_angle = (p_angle - rotation_speed) % 360
    # cheat mode (c key)
    if key == b'c':
        cheat_mode = not cheat_mode
        if not cheat_mode:
            gun_pov = False
    # cheat vision (v key)
    if key == b'v':
        gun_pov = not gun_pov
    if gun_pov:
        cam_coordinates[0] = 100; cam_coordinates[1] = 100; cam_coordinates[2] = 50
    else:
        cam_coordinates[0] = 300; cam_coordinates[1] = 500; cam_coordinates[2] = 350

    # reset game (r key)
    if key == b'r' and game_over:
        reset_game()
    glutPostRedisplay()
    # EXTRA ------------
    # Top View (t key)
    if key == b't':
        global top_view_mode
        top_view_mode = not top_view_mode
    # (o key)
    if key == b'o':
        global over_view_mode
        over_view_mode = not over_view_mode

def specialKeyListener(key, x, y):
    global cam_coordinates
    if key == GLUT_KEY_LEFT:
        cam_coordinates[0] -= 2
    elif key == GLUT_KEY_RIGHT:
        cam_coordinates[0] += 2
    elif key == GLUT_KEY_UP:
        cam_coordinates[1] += 2
    elif key == GLUT_KEY_DOWN:
        cam_coordinates[1] -= 2

def mouseListener(button, state, x, y):
    global first_person_view, hide_player_head
    if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN and not game_over:
        fire_bullet()
    if button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN:
        first_person_view = not first_person_view
        hide_player_head = first_person_view

def setupCamera():
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(fovY, 1.25, 0.1, 1500)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    if top_view_mode:
        gluLookAt(300, 300, 350,
                  300, 300, 0,     
                  0, 1, 0)      
    elif over_view_mode:
        gluLookAt(player_coordinate[0], player_coordinate[1] , 400,
                  player_coordinate[0], player_coordinate[1]+10, 0,
                  0, 0, 1)
    elif first_person_view:
        angle_rad = math.radians(p_angle)
        cam_x = player_coordinate[0] + 2
        cam_y = player_coordinate[1]
        cam_z = player_coordinate[2] + 50  
        l_x = cam_x + math.cos(angle_rad)
        l_y = cam_y + math.sin(angle_rad)
        l_z = cam_z
        gluLookAt(cam_x, cam_y, cam_z,
                  l_x, l_y, l_z,
                  0, 0, 1)
        
    elif gun_pov: # when v key is pressed
        cam_x = player_coordinate[0] + 5
        cam_y = player_coordinate[1] + 0  
        cam_z = player_coordinate[2] + 150  
        l_x = player_coordinate[0] + 100 
        l_y = player_coordinate[1]
        l_z = player_coordinate[2] + 50
        gluLookAt(cam_x, cam_y, cam_z,
                l_x, l_y, l_z,
                0, 0, 1)
    else:
        # defalut
        x, y, z = cam_coordinates
        gluLookAt(x, y, z,
                  300, 180, 0,
                  0, 0, 1)
        
last_fire_angle = None
occurance = 5

def update_cheat_mode():
    
    global p_angle, last_fire_angle
    if cheat_mode and not game_over:
        p_angle = (p_angle + cheat_rotation_speed) % 360
        best_enemy = None
        best_enemy_angle = None
        best_angle_diff = 360
        for enemy in enemies:
            dx = enemy[0] - player_coordinate[0]
            dy = enemy[1] - player_coordinate[1]

            enemy_angle = math.degrees(math.atan2(dy, dx)) % 360
            angle_diff = min((p_angle - enemy_angle) % 360, (enemy_angle - p_angle) % 360)
            if angle_diff < best_angle_diff:
                best_angle_diff = angle_diff
                best_enemy = enemy
                best_enemy_angle = enemy_angle

        if best_enemy and best_angle_diff < occurance:
            if last_fire_angle is None:
                fire_bullet()
                last_fire_angle = best_enemy_angle
            else:
                moved_angle = min((p_angle - last_fire_angle) % 360,
                                  (last_fire_angle - p_angle) % 360)
                if moved_angle > occurance:
                    fire_bullet()
                    last_fire_angle = best_enemy_angle

def idle():
    if not game_over:
        update_enemies()
        update_bullets()
        update_cheat_mode()
    glutPostRedisplay()

def showScreen():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()  # Reset modelview matrix
    glViewport(0, 0, 1000, 800)  # Set viewport size
    setupCamera()  # Configure camera perspective
    draw_grid()
    wall()
    draw_player()
    draw_enemies()
    draw_bullets()
# -------------------------- GRID ---------------------------------------
    if game_over:
        draw_text(20, 730, f"GAME OVER. Your Score is {score}")
        draw_text(20, 700, "Press "R" to Restart")
    else:
        draw_text(20, 760, f"Player Life Remaining: {lifes}")
        draw_text(20, 730, f"Game Score: {score}")
        draw_text(20, 700, f"Player Bullet Missed: {bullets_missed}")
    glutSwapBuffers()

def main():
    glutInit()
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)  # Double buffering, RGB color, depth test
    glutInitWindowSize(1000, 800)  # Window size
    glutInitWindowPosition(0, 0)  # Window position
    wind = glutCreateWindow(b"22299480_MihirDas_lab3")  # Create the window
    enemy_spawn()
    reset_game()
    glutDisplayFunc(showScreen)  # Register display function
    glutKeyboardFunc(keyboardListener)  # Register keyboard listener
    glutSpecialFunc(specialKeyListener)
    glutMouseFunc(mouseListener)
    glutIdleFunc(idle)  # Register the idle function to move the bullet automatically
    glutMainLoop()  # Enter the GLUT main loop

if __name__ == "__main__":
    main()