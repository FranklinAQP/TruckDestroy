
extends TextureButton

# member variables here, example:
# var a=2
# var b="textvar"

func _ready():
	# Called every time the node is added to the scene.
	# Initialization here
	pass




func _on_inicio_pressed():
	get_tree().change_scene("res://inicio.tscn")
