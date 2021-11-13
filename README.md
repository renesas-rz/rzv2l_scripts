# RZV2L Helper Scripts and Applications

### RZV2L DRP AI Evaluation Post Process

The RZV2L DRP AI includes evaluation software for Resnet50, Yolo, and TinyYolo. These neural networks were trained with the  ImageNet dataset. This data set has 1000 classes. The Evaluation Software has two modes Image and Camera. In addition the output of the evaluation software is a binary file that is parsed during post process. The steps below describe how to run the two evaluation software modes and how to use the post process code.

It is assumed that you have followed the instructions to build the RZV2L with DRP-AI and Codec. Loaded the  kernal, root filesystem, and boot loaders. These are described [here](https://renesas.info/wiki/RZ-V/RZ-V2L_SMARC).

#### Image Evaluation

***Step 1*** Connect to the RZV2L board with Serial or SSH. The latter needs Ethernet connection.

***Step 2*** Login to the board with password "root"

***Step 3*** The board should contain a folder called "RZV2L_AI_Eva_SW". If not go back rebuild the BSP with DRP-AI. enter the directory

***Step 4*** Execute the following command . This will run the evaluation software on a single image file.

```
./start_app.sh I
```

The output after execution is in the ./resnet50_bmp_output/bmp_img/ directory. 

- *.log 
  - there may be several of these. This records the commandline output.
- sample.bmp.bin
  - This is the neural network output binary

#### Camera Capture Evaluation

**Required Hardware:** 

- USB Camera Logitech C922X Pro Stream Webcam

***Step 1*** Connect to the RZV2L board with Serial or SSH. The latter needs Ethernet connection.

***Step 2*** Login to the board with password "root"

***Step 3*** The board should contain a folder called "RZV2L_AI_Eva_SW". If not go back rebuild the BSP with DRP-AI. enter the directory

***Step 4*** Execute the following command . This will run the evaluation software on a single image file.

```
./start_app.sh C
```

The output after execution is in the ./resnet50_bmp_output/bmp_img/ directory. 

- *.log 
  - there may be several of these. This records the commandline output.
- sample.bmp.bin
  - This is the neural network output binary

#### Post Processing

This section uses the eval_app project for post processing of the Evaluation Neural Networks (Resnet50, Yolo, Tiny Yolo ) trained with Imagenet. A binary is already included in the exe sub folder. Use this for the following steps.

Post Processing commads

```
./aipp NN_Name NN_Output_Filename
```

- NN_Name : The name of the supported Neural Network (NN). Supported NN are resnet, yolo, moblenet, and tinyyolo.
- NN_Output_Filename: This is the path and filename of the NN binary output file.

***Step 1*** In a terminal on a PC scp the binary file to the RZV2L directoy /home/root/RZV2L_AI_Eva_SW. 

```
scp aipp root@xxx.xxx.xxx.xxx:/home/root/RZV2L-AI_EVA_SW
```

***Step 2***  In the RZV2L terminal change the aipp command to an executabile.

```
chmod +x aipp
```

***Step 3*** On the RZV2L Terminal ( Serial or SSH) enter the following command

**Image Post Processing**

```
./aipp resnet ./resnet50_bmp_output/bmp_img/sample.bmp.bin

Post Processing AI Network Resnet50, Filename: ./resnet50_bmp_output/bmp_img/sample.bmp.bin
Decode Processing file: ./resnet50_bmp_output/bmp_img/sample.bmp.bin, Sample size: 1000
List of the top: 5
Top 0 : (  93.52) beagle
Top 1 : (   2.85) English_foxhound
Top 2 : (   2.85) Walker_hound
Top 3 : (   0.49) basset
Top 4 : (   0.10) bluetick
```

**Camera Post Processing**

*NOTE: There are more that one binary file for camera capture with the .bin extension.*

```
./aipp resnet ./resnet50_cam_output/capture/filename.bin

Post Processing AI Network Resnet50, Filename: ./resnet50_bmp_output/bmp_img/sample.bmp.bin
Decode Processing file: ./resnet50_bmp_output/bmp_img/sample.bmp.bin, Sample size: 1000
List of the top: 5
Top 0 : (  93.52) beagle
Top 1 : (   2.85) English_foxhound
Top 2 : (   2.85) Walker_hound
Top 3 : (   0.49) basset
Top 4 : (   0.10) bluetick
```
