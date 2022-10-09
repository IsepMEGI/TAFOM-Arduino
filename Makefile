sym-links:
	rm -f ./playground/*.cpp
	rm -f ./playground/*.h
	cp -s $(PWD)/main/*.h $(PWD)/playground
	cp -s $(PWD)/main/*.cpp $(PWD)/playground
