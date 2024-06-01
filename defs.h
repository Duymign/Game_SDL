#ifndef _DEFS_H
#define _DEFS_H

//Screen dimension constants
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 768

//MAP
#define MAX_MAP_X 120
#define MAX_MAP_Y 12
#define TILE_SIZE 64
#define MAX_TILE 19
//
const int fps = 50;

//Main Object
#define Width_main_object 75
#define Height_main_Object 90
const int Main_Max_Hp = 100;

const int frame_width =715/6;
const int frame_height =110;

const int frame_height_jump = 1023 ;
const int frame_width_jump = 4984/7;

const int frame_width_attack = 5580/ 5;
const int frame_height_attack = 1080;

const int frame_height_shoot = 110;
const int frame_width_shoot = 345/ 3;
const int frame_height_die = 265;
const int frame_width_die = 1325/5;

const int frame_height_skill = 408;
const int frame_width_skill = 6000/6;
const int timeSetSkill = 5000;
const int timeSetAttack = 300;
const int timeSetShoot = 600;

const float character_speed = Width_main_object/4 ;
const float gravity_speed = 1.2;

#define MAX_FALL_SPEED 6
#define ATTACK_DAMGE 10
#define SHOOT_DAMGE 15
#define SKILL_DAMGE 20

//Dart
const int Width_Dart = 35;
const int Height_Dart = 35;
#define DART_SPEED 25

//Boss
#define Width_boss_object 150
#define Height_boss_object 180
const int boss_frame_width_run = 6218/6;
const int boss_frame_height_run = 1054;
const int boss_frame_width_attack = 285;
const int boss_frame_height_attack = 261;
const int boss_frame_height_die = 245;
const int boss_frame_width_die = 1800/6;
const int boss_frame_height_skill = 246;
const int boss_frame_width_skill = 850/5;
const int boss_skill_speed = 10;
const int boss_width_skill = 70;
const int boss_heigh_skill = 200;


const int boss_speed = character_speed;
#define BOSS_MAX_HP 1000
#define BOSS_DAMAGE 10
#define BOSS_SKILL_DAMAGE 15

//Enemy
#define Width_enemy_object 80
#define Height_enemy_object 100
const int enemy_frame_width_run = 1452/6;
const int enemy_frame_height_run = 265;
const int enemy_frame_width_attack = 1472/4;
const int enemy_frame_height_attack = 264;
const int enemy_speed = Width_enemy_object / 3;
const int enemy_frame_width_hurt = 640/2;
const int enemy_frame_height_hurt = 317;
const int enemy_frame_height_die = 261;
const int enemy_frame_width_die = 1960/4;

#define ENEMY_MAX_HP 60
#define ENEMY_DAMGE 4

//MiniMap
#define MINI_MAP_RADIUS 80

#endif // _DEFS_H
