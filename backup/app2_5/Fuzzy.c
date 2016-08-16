/******************************************************************************
*******************************************************************************
*                           Freescale-������ѧ--ӣ                            *
*                               ģ���㷨�ӳ���                                *
*                                                                             *
*                                                                             *
*                                                                             *
*                                                                             *
*                                               Miz.Wong                      *
*                                                  @                          *
*                                             Innovation.Lab                  *
*******************************************************************************/
#include "common.h"
#include "Fuzzy.h"

/**********************************************************************
* �������ƣ�FuzzyCtrl
* �������ܣ�ģ���� ȥģ��
* ��ڲ�����FuzzyStruct* Fuzzy_S
* ���ڲ�����Fuzzy Value
**********************************************************************/
float FuzzyCtrl(FuzzyStruct* Fuzzy_S)
{
  float  eFuzzy[2] = { 0.0, 0.0 };//ƫ��
  float  ecFuzzy[2] = { 0.0, 0.0 };//ƫ��΢��
  float  QRule[4] = { 0.0, 0.0, 0.0, 0.0 }; //URule[]���ֵ
  float  U1Fuzzy[4] = { 0.0, 0.0, 0.0, 0.0 }; //���ֵ��������
  int  pe = 0, pec = 0, U1Rule[4] = { 0, 0, 0, 0 };//ƫ��  ƫ��ı仯��  ���õ���������
  float U = 0;//���ֵ�ľ�ȷ��
  int rank;//�����ȼ���
  float   temp1, temp2;//���ķ��м����
  rank = Fuzzy_S->Rank;
  
  /*----------------------------------------ģ����������------------------------------------------*/
  switch (rank)
  {
  case 9:
    {
      /*-----���������������-----*/
      if (Fuzzy_S->fe <= Fuzzy_S->eRule[0])		            // |x_x_x_x_x_x_x_x_x_
      {
        eFuzzy[0] = 1.0;
        pe = -3;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[1])	         // _x|x_x_x_x_x_x_x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[1] - Fuzzy_S->fe) / (Fuzzy_S->eRule[1] - Fuzzy_S->eRule[0]);//�ƽ��̶ȱ��� ��һ��
        pe = -3;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[2])	        // _x_x|x_x_x_x_x_x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[2] - Fuzzy_S->fe) / (Fuzzy_S->eRule[2] - Fuzzy_S->eRule[1]);
        pe = -2;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[3])	        // _x_x_x|x_x_x_x_x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[3] - Fuzzy_S->fe) / (Fuzzy_S->eRule[3] - Fuzzy_S->eRule[2]);
        pe = -1;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[4])		    // _x_x_x_x|x_x_x_x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[4] - Fuzzy_S->fe) / (Fuzzy_S->eRule[4] - Fuzzy_S->eRule[3]);
        pe = 0;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[5])		     // _x_x_x_x_x|x_x_x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[5] - Fuzzy_S->fe) / (Fuzzy_S->eRule[5] - Fuzzy_S->eRule[4]);
        pe = 1;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[6])		     // _x_x_x_x_x_x|x_x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[6] - Fuzzy_S->fe) / (Fuzzy_S->eRule[6] - Fuzzy_S->eRule[5]);
        pe = 2;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[7])		     // _x_x_x_x_x_x_x|x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[7] - Fuzzy_S->fe) / (Fuzzy_S->eRule[7] - Fuzzy_S->eRule[6]);
        pe = 3;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[8])		     // _x_x_x_x_x_x_x_x|x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[8] - Fuzzy_S->fe) / (Fuzzy_S->eRule[8] - Fuzzy_S->eRule[7]);
        pe = 4;
      }
      else if (Fuzzy_S->fe >= Fuzzy_S->eRule[8])			     // _x_x_x_x_x_x_x_x_x|
      {
        eFuzzy[0] = 0;
        pe = 4;
      }
      eFuzzy[1] = 1 - eFuzzy[0];
      
      /*-----���仯������������---*/
      if (Fuzzy_S->fec <= Fuzzy_S->ecRule[0])
      {
        ecFuzzy[0] = 1.0;
        pec = -3;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[1])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[1] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[1] - Fuzzy_S->ecRule[0]); //�ƽ��̶ȱ���
        pec = -3;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[2])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[2] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[2] - Fuzzy_S->ecRule[1]);
        pec = -2;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[3])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[3] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[3] - Fuzzy_S->ecRule[2]);
        pec = -1;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[4])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[4] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[4] - Fuzzy_S->ecRule[3]);
        pec = 0;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[5])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[5] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[5] - Fuzzy_S->ecRule[4]);
        pec = 1;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[6])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[6] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[6] - Fuzzy_S->ecRule[5]);
        pec = 2;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[7])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[7] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[7] - Fuzzy_S->ecRule[6]);
        pec = 3;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[8])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[8] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[8] - Fuzzy_S->ecRule[7]);
        pec = 4;
      }
      else
      {
        ecFuzzy[0] = 0;
        pec = 4;
      }
      
      ecFuzzy[1] = 1 - ecFuzzy[0];
      break;
    }//...9��������
    
  case 7:
    {
      /*-----���������������-----*/
      if (Fuzzy_S->fe <= Fuzzy_S->eRule[0])		        // |x_x_x_x_x_x_x_
      {
        eFuzzy[0] = 1.0;
        pe = -2;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[1])	        // _x|x_x_x_x_x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[1] - Fuzzy_S->fe) / (Fuzzy_S->eRule[1] - Fuzzy_S->eRule[0]);//�ƽ��̶����� ��һ������
        pe = -2;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[2])	        // _x_x|x_x_x_x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[2] - Fuzzy_S->fe) / (Fuzzy_S->eRule[2] - Fuzzy_S->eRule[1]);
        pe = -1;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[3])	        // _x_x_x|x_x_x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[3] - Fuzzy_S->fe) / (Fuzzy_S->eRule[3] - Fuzzy_S->eRule[2]);
        pe = 0;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[4])		        // _x_x_x_x|x_x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[4] - Fuzzy_S->fe) / (Fuzzy_S->eRule[4] - Fuzzy_S->eRule[3]);
        pe = 1;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[5])		        // _x_x_x_x_x|x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[5] - Fuzzy_S->fe) / (Fuzzy_S->eRule[5] - Fuzzy_S->eRule[4]);
        pe = 2;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[6])		        // _x_x_x_x_x_x|x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[6] - Fuzzy_S->fe) / (Fuzzy_S->eRule[6] - Fuzzy_S->eRule[5]);
        pe = 3;
      }
      else if (Fuzzy_S->fe >= Fuzzy_S->eRule[6])			  // _x_x_x_x_x_x_x|
      {
        eFuzzy[0] = 0;
        pe = 3;
      }
      eFuzzy[1] = 1 - eFuzzy[0];
      
      /*-----���仯��������������-----*/
      if (Fuzzy_S->fec <= Fuzzy_S->ecRule[0])
      {
        ecFuzzy[0] = 1.0;
        pec = -2;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[1])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[1] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[1] - Fuzzy_S->ecRule[0]);
        pec = -2;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[2])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[2] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[2] - Fuzzy_S->ecRule[1]);
        pec = -1;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[3])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[3] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[3] - Fuzzy_S->ecRule[2]);
        pec = 0;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[4])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[4] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[4] - Fuzzy_S->ecRule[3]);
        pec = 1;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[5])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[5] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[5] - Fuzzy_S->ecRule[4]);
        pec = 2;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[6])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[6] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[6] - Fuzzy_S->ecRule[5]);
        pec = 3;
      }
      else
      {
        ecFuzzy[0] = 0;
        pec = 3;
      }
      
      ecFuzzy[1] = 1 - ecFuzzy[0];
      break;
      
    }//...7�������� 
    
  case 5:
    {
      /*-----���������������-----*/
      if (Fuzzy_S->fe <= Fuzzy_S->eRule[0])			// |x_x_x_x_x_ 
      {
        eFuzzy[0] = 1.0;
        pe = -1;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[1])               // _x|x_x_x_x_ 
      {
        eFuzzy[0] = (Fuzzy_S->eRule[1] - Fuzzy_S->fe) / (Fuzzy_S->eRule[1] - Fuzzy_S->eRule[0]);
        pe = -1;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[2])               // _x_x|x_x_x_ 
      {
        eFuzzy[0] = (Fuzzy_S->eRule[2] - Fuzzy_S->fe) / (Fuzzy_S->eRule[2] - Fuzzy_S->eRule[1]);
        pe = 0;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[3])               // _x_x_x|x_x_ 
      {
        eFuzzy[0] = (Fuzzy_S->eRule[3] - Fuzzy_S->fe) / (Fuzzy_S->eRule[3] - Fuzzy_S->eRule[2]);
        pe = 1;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[4])		        // _x_x_x_x|x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[4] - Fuzzy_S->fe) / (Fuzzy_S->eRule[4] - Fuzzy_S->eRule[3]);
        pe = 2;
      }
      else							// _x_x_x_x_x| 
      {
        eFuzzy[0] = 0;
        pe = 2;
      }
      eFuzzy[1] = 1 - eFuzzy[0];
      
      /*-----���仯��������������-----*/
      if (Fuzzy_S->fec <= Fuzzy_S->ecRule[0])
      {
        ecFuzzy[0] = 1.0;
        pec = -1;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[1])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[1] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[1] - Fuzzy_S->ecRule[0]);
        pec = -1;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[2])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[2] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[2] - Fuzzy_S->ecRule[1]);
        pec = 0;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[3])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[3] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[3] - Fuzzy_S->ecRule[2]);
        pec = 1;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[4])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[4] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[4] - Fuzzy_S->ecRule[3]);
        pec = 2;
      }
      else
      {
        ecFuzzy[0] = 0;
        pec = 2;
      }
      
      ecFuzzy[1] = 1 - ecFuzzy[0];
      break;
    }//...5��������
    
  case 3:
    {
      /*-----���������������-----*/
      if (Fuzzy_S->fe <= Fuzzy_S->eRule[0])			// |x_x_x_
      {
        eFuzzy[0] = 1.0;
        pe = 0;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[1])		// _x|x_x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[1] - Fuzzy_S->fe) / (Fuzzy_S->eRule[1] - Fuzzy_S->eRule[0]);
        pe = 0;
      }
      else if (Fuzzy_S->fe <= Fuzzy_S->eRule[2])		// _x_x|x_
      {
        eFuzzy[0] = (Fuzzy_S->eRule[2] - Fuzzy_S->fe) / (Fuzzy_S->eRule[2] - Fuzzy_S->eRule[1]);
        pe = 1;
      }
      else							// _x_x_x|
      {
        eFuzzy[0] = 0;
        pe = 1;
      }
      eFuzzy[1] = 1 - eFuzzy[0];
      
      /*-----���仯��������������-----*/
      if (Fuzzy_S->fec <= Fuzzy_S->ecRule[0])
      {
        ecFuzzy[0] = 1.0;
        pec = 0;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[1])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[1] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[1] - Fuzzy_S->ecRule[0]);
        pec = 0;
      }
      else if (Fuzzy_S->fec <= Fuzzy_S->ecRule[2])
      {
        ecFuzzy[0] = (Fuzzy_S->ecRule[2] - Fuzzy_S->fec) / (Fuzzy_S->ecRule[2] - Fuzzy_S->ecRule[1]);
        pec = 1;
      }
      else
      {
        ecFuzzy[0] = 0;
        pec = 1;
      }
      
      ecFuzzy[1] = 1 - ecFuzzy[0];
      break;
    }//...3�������� 
  default: break;
  }//�������������
  
  /*��ѯģ������� rule[][]*/
  /*����ֵ��URule[]���*/
  /*һ�㶼���ĸ�������Ч*/
  U1Rule[0] = Fuzzy_S->rule[pe - 1 + 3][pec - 1 + 3];
  U1Rule[1] = Fuzzy_S->rule[pe + 3][pec - 1 + 3];
  U1Rule[2] = Fuzzy_S->rule[pe - 1 + 3][pec + 3];
  U1Rule[3] = Fuzzy_S->rule[pe + 3][pec + 3];
  
  
  //���������
  if (eFuzzy[0] <= ecFuzzy[0]) // 0-0
    U1Fuzzy[0] = eFuzzy[0];
  else
    U1Fuzzy[0] = ecFuzzy[0];
  
  if (eFuzzy[1] <= ecFuzzy[0]) // 1-0
    U1Fuzzy[1] = eFuzzy[1];
  else
    U1Fuzzy[1] = ecFuzzy[0];
  
  if (eFuzzy[0] <= ecFuzzy[1]) // 0-1
    U1Fuzzy[2] = eFuzzy[0];
  else
    U1Fuzzy[2] = ecFuzzy[1];
  
  if (eFuzzy[1] <= ecFuzzy[1]) // 1-1
    U1Fuzzy[3] = eFuzzy[1];
  else
    U1Fuzzy[3] = ecFuzzy[1];
  
  /*ͬ���������������ֵ���*/
  
  if (U1Rule[0] == U1Rule[1])
  {
    if (U1Fuzzy[0]>U1Fuzzy[1])
      U1Fuzzy[1] = 0;
    else
      U1Fuzzy[0] = 0;
  }
  if (U1Rule[0] == U1Rule[2])
  {
    if (U1Fuzzy[0]>U1Fuzzy[2])
      U1Fuzzy[2] = 0;
    else
      U1Fuzzy[0] = 0;
  }
  if (U1Rule[0] == U1Rule[3])
  {
    if (U1Fuzzy[0]>U1Fuzzy[3])
      U1Fuzzy[3] = 0;
    else
      U1Fuzzy[0] = 0;
  }
  if (U1Rule[1] == U1Rule[2])
  {
    if (U1Fuzzy[1]>U1Fuzzy[2])
      U1Fuzzy[2] = 0;
    else
      U1Fuzzy[1] = 0;
  }
  if (U1Rule[1] == U1Rule[3])
  {
    if (U1Fuzzy[1]>U1Fuzzy[3])
      U1Fuzzy[3] = 0;
    else
      U1Fuzzy[1] = 0;
  }
  if (U1Rule[2] == U1Rule[3])
  {
    if (U1Fuzzy[2]>U1Fuzzy[3])
      U1Fuzzy[3] = 0;
    else
      U1Fuzzy[2] = 0;
  }
  
  /*���ķ���ģ��*/
  /*U1Rule[]ԭֵΪ�������������ţ�ת��ΪURule[]��������ֵ*/
  if (U1Rule[0] >= 0)
    QRule[0] = Fuzzy_S->URule[U1Rule[0]];
  else
    QRule[0] = -(Fuzzy_S->URule[-U1Rule[0]]);
  
  if (U1Rule[1] >= 0)
    QRule[1] = Fuzzy_S->URule[U1Rule[1]];
  else
    QRule[1] = -(Fuzzy_S->URule[-U1Rule[1]]);
  
  if (U1Rule[2] >= 0)
    QRule[2] = Fuzzy_S->URule[U1Rule[2]];
  else
    QRule[2] = -(Fuzzy_S->URule[-U1Rule[2]]);
  
  if (U1Rule[3] >= 0)
    QRule[3] = Fuzzy_S->URule[U1Rule[3]];
  else
    QRule[3] = -(Fuzzy_S->URule[-U1Rule[3]]);
  
  temp1 = U1Fuzzy[0] * QRule[0] + U1Fuzzy[1] * QRule[1] + U1Fuzzy[2] * QRule[2] + U1Fuzzy[3] * QRule[3];
  temp2 = U1Fuzzy[0] + U1Fuzzy[1] + U1Fuzzy[2] + U1Fuzzy[3];
  U = temp1 / temp2;
  return U;
}

/**********************************************************************
* �������ƣ�Fuzzy_Update
* �������ܣ�ģ�����Ƹ���
* ��ڲ�����FuzzyStruct* F_S
ek
ekc
* ���ڲ�����Fuzzy Value
**********************************************************************/
float Fuzzy_Update(FuzzyStruct* F_S, float ek, float ekc)
{
  float value = 0;
  F_S->fe = ek;
  F_S->fec = ekc;
  value = FuzzyCtrl(F_S);
  return value;
}