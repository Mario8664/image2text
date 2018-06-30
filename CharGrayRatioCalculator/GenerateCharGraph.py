#This is a simple tool that can generate common char to jpg graph.
import pygame
import os
pygame.init()
folder = os.path.exists('AllFontSymbol')
if not folder:
	os.makedirs('AllFontSymbol')

for i in range(33,126):
	font = pygame.font.SysFont('Courier New', 108)
	ftext = font.render(chr(i), True, (0,0,0),(255, 255, 255))
	pygame.image.save(ftext, "AllFontSymbol/"+str(i)+".jpg")

