
extends Area2D

# member variables here, example:
# var a=2
# var b="textvar"

const SPEED = 200.0
var muerto = false
var prev_shoot = false
var tmp=0

func matate():
	if(muerto):
		return
	get_node("Sprite").hide()
	get_node("explosion").set_emitting(true)
	muerto=true




func _process(delta):
	var dir = Vector2()
	if(Input.is_action_pressed("move_down")):
		dir+=Vector2(0,1)
	if(Input.is_action_pressed("move_up")):
		dir+=Vector2(0,-1)
	if(Input.is_action_pressed("move_left")):
		dir+=Vector2(-1,0)
	if(Input.is_action_pressed("move_right")):
		dir+=Vector2(1,0)
	
	#translate(dir * delta * SPEED)
	var pos = get_pos()
	pos += dir*delta*SPEED
	var size = get_viewport_rect().size
	pos.x = clamp(pos.x, 0, size.x)
	pos.y = clamp(pos.y, 0, size.y)
	set_pos(pos)
	#pass
	var shoot = Input.is_action_pressed("shoot")
	
	if(shoot and not prev_shoot):
		var shoot1 = preload("res://Disparo.tscn")
		var shoot_scene = shoot1.instance()
		shoot_scene.set_pos(pos)
		shoot_scene.add_to_group("shoott")
		get_parent().add_child(shoot_scene)
	prev_shoot = shoot
	if(muerto):
		tmp+=1
		if(tmp>50):
			get_tree().change_scene("res://perdio.tscn")
	#get_node("puntaje").set_text("Puntaje: "+str(p))
	
func _ready():
	set_process(true)


