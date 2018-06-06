/*
 * Copyright 1993-2015 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */

//prepare_data()
//data_calculation()
//disaply()

#include <opencv2/opencv.hpp>
#include <stdio.h>
#define F_ROW (2048)
#define F_COL (3000)
#define F_SZ (F_ROW*F_COL)
#define DEPTH (sizeof(unsigned short))
#define SPEC_SZ (2048 * sizeof(float))
using namespace cv;

void write_raw_image(void *raw_image,const char *filename, unsigned int size)
{
    FILE *out_fp;
    out_fp = fopen(filename, "wb");
    fwrite(raw_image,1,size,out_fp);
    fclose(out_fp);

}


int main()
{
	FILE *fp;
	void *frame;
	void *bg_frame;
	float *spec;

	frame = malloc(F_SZ * DEPTH);
	fp = fopen("resource/input_graph/frame13508.2048.SDOCT.dat","rb");
	fread(frame, DEPTH, F_SZ, fp);
	fclose(fp);


	bg_frame = malloc(F_SZ * DEPTH);
	fp = fopen("resource/bg_files/frame00234.2048.SDOCT.dat", "rb");
	fread(bg_frame, DEPTH, F_SZ, fp);
	fclose(fp);

	
	spec = (float *)malloc(SPEC_SZ);
	fp = fopen("resource/spectrum/frame13508.spectrum", "r");
	for(int i; i < 2048; i++)
		fscanf(fp, "%f", &spec[i]);
	fclose(fp);

	Mat mat_frame(F_ROW, F_COL, CV_8U, frame);
	write_raw_image(mat_frame.ptr(), "2048x3000_SRC", 2048*3000*2 );
	namedWindow("OCT");
	imshow("OCT", mat_frame);

	waitKey(0);

	destroyWindow("OCT");
	mat_frame.release();
	free(frame);
	free(spec);
	free(bg_frame);
	return 0;
}
