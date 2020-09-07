#include "gdal_methods.hpp"


//get trans of tiff file
/*
 @prama: const char * file_path_name -- file path to load the tif
 @prama: double* trans -- array to record the trans
 */
void getTrans_of_TiffFile(const char * file_path_name, double* trans){
    GDALDataset *poDataset;   //GDAL数据集
    GDALAllRegister();  //注册所有的驱动
    poDataset = (GDALDataset *) GDALOpen(file_path_name, GA_ReadOnly );
    if( poDataset == NULL )
    {
        cout<<"fail in open files!!!"<<endl;

    }
    
       //获取坐标变换系数
    //double trans[6];
    CPLErr aaa=poDataset->GetGeoTransform(trans);
    
    delete poDataset;

    
}

//get the row,column subnum in tiff file from spacial loacation geoX geoY
/*
 @prama: double *trans -- array record thr trans data
 @prama: double geoX -- input the spacial location_X
 @prama: double geoY -- input the spacial location_Y
 @prama: int type -- decide the return type 2--row other--column
 return : the row or column for input spacial XY
 */
float get_row_column_frm_geoX_geoY(double *trans,double geoX, double geoY,int type){
    
    double dTemp = trans[1] * trans[5] - trans[2] * trans[4];
    
    float dCol = (trans[5] * (geoX - trans[0]) - trans[2] * (geoY - trans[3])) / dTemp + 0.5;//移到像素中心
	float dRow = (trans[1] * (geoY - trans[3]) - trans[4] * (geoX - trans[0])) / dTemp + 0.5;
    
    if(type == 2){
        
        return dRow;
    }
    
    return dCol;
}


