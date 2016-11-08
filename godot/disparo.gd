
extends Area2D

const SPEED = -250
# member variables here, example:
# var a=2
# var b="textvar"
func _process(delta):
	translate(Vector2(0, SPEED*delta))

func _ready():
	# Called every time the node is added to the scene.
	# Initialization here
	set_process(true)
	pass

func _on_VisibilityNotifier2D_exit_screen():
	queue_free()
	pass


