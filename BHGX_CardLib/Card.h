#ifndef _CARD_H
#define _CARD_H
#include <assert.h>

#ifdef  __cplusplus
extern "C" {
#endif


#define	CARDSEAT_RF		0	//���ǽ��û��� 
#define CARDSEAT_PSAM1	1	//1��SAM�����1
#define CARDSEAT_M1		2	//2��M1

#define CMD_BEEP	1
#define CMD_LED		2

typedef unsigned char BYTE;

//CPUÿ���ֶε�����
typedef enum eItemType
{
	eAnsType,
	eCnType,
	eBType,
}eItemType;

//CPU���ļ�����
typedef enum eFileType
{
	eBinType = 0,   
	eRecType,       
	eCycType,            //ѭ���ļ�������appendRec
	eSureType            //�����ļ�,����SignRec
}eFileType;


/**
* @ID 
* @MASK 
* @TYPE 
* @CHECK 
* @SOURCE 
* @TARGET
* @DEFAULT 
* @ISWRITE 
* @OFFSET 
* @COLUMNBIT 
* @INULLABLE= 
* @WRITEBACK
*/
typedef struct M1Type {
	char	Mask		:1;
	char	Type		:3;
	char	Check		:1;
	char	IsWrite		:1;
	char	INullLable	:1;
	char	WriteBack	:1;
	int		ColumnBit;
}M1Type;

typedef struct CpuInfo {
	eItemType	itemtype;
	int			ColumnByte;
}CpuInfo;

struct XmlColumnS
{
	int		ID;
	char	Source[32];

	union {
		M1Type   M1Info;
		CpuInfo  CpuInfo;
	}CheckInfo;

	int		Offset;
	char	*Value;
	struct XmlSegmentS  *parent;
	struct XmlColumnS	*Next;
};


/**
* @ID
* @TARGET
*/
struct XmlSegmentS
{
	int		ID;
	char	Target[30];

	//cpu
	int					offset;
	eFileType			datatype;

	struct XmlColumnS	*ColumnHeader;
	struct XmlColumnS   *ColumnTailer;
	struct XmlSegmentS	*Next;
};



/**
*@ID 
*@TARGET
*/
struct XmlProgramS
{
	int		ID;
	char	Target[50];

	struct XmlSegmentS		*SegHeader;
	struct XmlSegmentS		*SegTailer;
	struct XmlProgramS		*Next;
};
struct RWRequestS
{
	int	mode;	// ��д�����־

	int offset;	// ���Ե�ַƫ����
	//int startID;	//��ʼ��¼��ID
	//int recCounts;  //��¼����
	int	length;	// ��Ԫ�صĳ���
	unsigned char *value;

	//cpu
	int nID;    // ���
	int nColumID;  
	eFileType	datatype;
	eItemType   itemtype;

	struct RWRequestS *agent;	// ��ʵ�Ķ�д����

	void *pri;	

	// ��һ��Ԫ��
	struct RWRequestS	*Next;
};

//��ʼ����Ĺ���
typedef int					(*LastInit) (void*);

//����xml����ʼ������
typedef int					(*InitGlobalList)();

//Ϊ���������ڴ�
typedef int					(*CallocForList)(struct RWRequestS*);

typedef int					(*ConvertXmlByList) (struct XmlSegmentS *listHead, 
												 char *xml, int *length);
typedef struct XmlSegmentS* (*ConvertXmltoList) (char *xml);

typedef int                 (*ReadCard)(struct RWRequestS *list, void *apt);
typedef int                 (*WriteCard)(struct RWRequestS *list,  void *apt);

typedef void				(*CallocForColmn)(struct XmlColumnS *);

typedef enum CardType
{
	eM1Card = 0,
	eCPUCard,
	eCARDSEAT_PSAM1,
}CardType;

#define ARRAY_MAX 10

typedef struct adapter{
	CardType			type;
	LastInit			iLastInit;
	CallocForList		iCallocForList;
	ReadCard			iReadCard;
	WriteCard			iWriteCard;

	void				*parent;
}adapter;


typedef struct CardOps 
{
	InitGlobalList		iInitGList;
	ConvertXmlByList	iConvertXmlByList;
	ConvertXmltoList	iConvertXmltoList;
	CallocForColmn      iCallocForColmn;

	adapter		      *cardAdapter;
}CardOps;

void      CardUnregisterOps(int type);

void      CardRegisterOps(int type, CardOps *ops);

CardOps*  GetCardOps(int type);

int       IsAllTheSameFlag(const unsigned char *szBuf,
					       int nLen, unsigned char cflag);

#ifdef  __cplusplus
};
#endif


#endif