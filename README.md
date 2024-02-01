# splitbyintensity

takes an input image on the command line, and an output prefix and splits the image into 10 images with the level  of intensity from 0 to 255 into 10 ranges, the images should not overlap and black becomes transparent.


splitbyintensity input.png output (where lower and upper are the values used from the intensity range being 0 - 255 )

generates 10 files called output_lower_upper.png

i use this for laser cutter artwork so i can specify different settings for different parts of the image. i load them into lightburn on seperate layers and adjust settings as needed.

builds with vcpkg and msvc, also with CMake now, the github workflows can generate and upload the artifacts (unsigned so mac needs exceptions)
