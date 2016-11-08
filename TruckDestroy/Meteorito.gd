
extends Area2D

# member variables here, example:
# var a=2
# var b="textvar"

func _ready():
	# Called every time the node is added to the scene.
	# Initialization here
	pass

func _on_Meteorito_area_enter(area):
	print(area.get_name())
	if(area.get_name()=="Nave"):
		area.matate()
	if(area.get_groups().find("shoott")!=-1):
		queue_free()
		area.queue_free()
	#	p=1
	
		
		
		
	pass # replace with function bod
