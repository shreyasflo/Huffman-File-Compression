Instructions

The repository contains the following files :
	
	1) program.cpp the source file
	2) program.exe the application file
	3) program.o the object file
	4) original HDF5 file googlenet_weights.h5
	5) comressed HDF5 file compressed.h5
	6) uncompressed HDF5 file uncompressed.h5

1) Navigate to the directory containing program.exe and the CPP source file on the command line
2) Type the following in the command prompt to execute the program
			
			This encodes by default and shows the building of huffman tree in real time 
			program -i googlenet_weights.h5 -o compressed.h5 -v	
				
						or
			
			This encodes without displaying the huffman tree building
			program -i googlenet_weights.h5 -o compressed.h5 -e		
						
			-i option is mandatory ( denotes input file)
			-o option is mandatory (denotes output file)
			-v option is optional
			-e denotes compression 

			This uncompresses the compressed file 
			
			program -i compressed.h5 -o uncompressed.h5 -d
			-d option denotes uncompression

The compressed file(compressed.h5) has size of 47.6MB compared to 51.2MB of original file(googlenet_weights.h5)
I was able to make the size of the compressed file to be 92.96% of size of the original file 
The uncompressed.h5 file has same size as the file googlenet_weights.h5 (lossless data compression and decompression)

