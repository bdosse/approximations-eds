#ifndef LIBSDS_H
#define LIBSDS_H


typedef enum {INT=1, UINT, DOUBLE} data_t;
typedef enum {UNDEF=0, UNIT, ARRAY} generic_t;
typedef enum {SDS_ERR_TYPE=-256, SDS_ERR_NULL, SDS_NULL_FORMAT_STRING,
  SDS_ERR_NULL_MEMBER} sds_error_t;

struct generic_unit
{
  /*
   * Encapsulates some often used basic data types.
   */
  
  data_t type;
  union
  {
    int _int;
    unsigned int _uint;
    double _double;
  };
};

struct generic_array
{
  /*
   * Encapsulates some pointers to often used data types.
   */
  
  data_t type;
  unsigned int size;
  union
  {
    int *_int;
    unsigned int *_uint;
    double *_double;
  };
};

struct simplified_data_structure
{
  /*
   * Encapsulates often used data types or pointers to data
   * types. 
   *
   * Members of this struct can be read easily: 
   *
   * ---
   *
   * 1) Check structure type;
   *
   * 2) If type is UNDEF, undefinite behaviour may arise at some
   * point. In particular, don't access the union member unless you
   * know what you're doing;
   *
   * 3) If the type is UNIT or ARRAY, treat the union member -- call
   * it U -- accordingly. The data type in U is stored in U.type;
   *
   * 4) If U.type is INT (resp. UINT, DOUBLE), the data is stored
   * in U._int (resp. U._uint, U._double).
   *
   * ---
   *
   * WARNING: in order to avoid undefinite behaviour, it is STRONGLY
   * advised not to write in members manually. Prefer using functions
   * below.
   *
   * When it comes to pointers, the struct shall be the sole owner,
   * i.e. any manipulation to the said pointer shall be made through
   * the struct.
   */
  
  unsigned int precision; /* used in printf for double */
  generic_t type; /* check what kind of generic is in use */
  union
  {
    struct generic_unit unit;
    struct generic_array array;
  };
};

typedef struct simplified_data_structure sds;

extern sds *
init_sds(void);
extern void
sds_store_unit_int(sds *atom, int item);
extern void
sds_store_unit_uint(sds *atom, unsigned int item);
extern void
sds_store_unit_double(sds *atom, double item);
extern void
sds_store_array_int(sds *atom, int *arr, unsigned int arr_size);
extern void
sds_store_array_uint(sds *atom, unsigned int *arr, unsigned int arr_size);
extern void
sds_store_array_double(sds *atom, double *arr, unsigned int arr_size);
extern void
sds_store_precision(sds *atom, unsigned int prec);



#endif /* LIBSDS_H */
