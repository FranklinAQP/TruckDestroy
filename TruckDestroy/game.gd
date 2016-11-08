
extends Node2D

# member variables here, example:
# var a=2
# var b="textvar"
var p = 0
var pg = 0

var time_g=0
var time_a=0
var time_b=0
var time_c=0
var time_d=0
var time_temp=0
var level=""
var marc=0
var marc2=0
var marc3=0
var marc4=0
var marc5=0

func get_puntaje():
	var temp = 0
	temp = get_node("enemigos").get_child_count() + get_node("enemigos2").get_child_count()+get_node("enemigos3").get_child_count()+get_node("enemigos4").get_child_count()+get_node("enemigos5").get_child_count()
	p = pg - temp

func get_level():
	if(time_g<15):
		level="NIVEL 1"
	elif(time_g<29):
		level="NIVEL 2"
	elif(time_g<40):
		level="NIVEL 3"
	elif(time_g<50):
		level="NIVEL 4"
	elif(time_g<58):
		level="NIVEL 5"
	else:
		level="GANOOOOOOO"

func sumar_reloj():
	
	if(time_temp>60):
		time_g += 1
		if(time_d==9):
			if(time_c==5):
				if(time_b==9):
					time_a += 1
					time_b = 0
					time_c = 0
					time_d = 0
				else:
					time_b += 1
					time_c = 0
					time_d = 0
			else:
				time_c += 1
				time_d = 0
		else:
			time_d += 1
		time_temp = 0
	else:
		time_temp += 1


func _process(delta):	
	sumar_reloj()
	get_node("reloj").set_text("Tiempo: "+str(time_a)+str(time_b)+":"+str(time_c)+str(time_d))
	get_level()
	get_node("nivel").set_text(level)
	if(time_g==65):
		get_tree().change_scene("res://gano.tscn")
	get_puntaje()
	get_node("puntaje").set_text("Puntaje: "+str(p))


func _ready():
	marc = get_node("enemigos").get_child_count()
	marc2 = get_node("enemigos2").get_child_count()
	marc3 = get_node("enemigos3").get_child_count()
	marc4 = get_node("enemigos4").get_child_count()
	marc5 = get_node("enemigos5").get_child_count()
	pg = marc + marc2 + marc3 + marc4 + marc5
	set_process(true)


