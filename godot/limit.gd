
extends Area2D

# member variables here, example:
# var a=2
# var b="textvar"

func _ready():
	# Called every time the node is added to the scene.
	# Initialization here
	pass


func _on_limit_area_enter(area):
	print(area.get_name())
	if(area.get_groups().find("shoot")!=-1):
		area.queue_free()
	pass # replace with function bod