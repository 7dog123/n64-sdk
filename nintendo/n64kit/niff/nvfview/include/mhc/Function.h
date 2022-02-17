/*
  mhc/Function.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 18, 1999.
*/

#ifndef _mhc_Function_h
#define _mhc_Function_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare Macro */
#define MHC_FUNCTION_CONTINUITY_DISCONT	(0)
#define MHC_FUNCTION_CONTINUITY_C0	(1)
#define MHC_FUNCTION_CONTINUITY_C1	(2)

/* Declare prototype structure */
struct _MhcFunction;

/* Declare types of a structure */
typedef u32 ( *MhcFunctionGetValueFunc )(
			struct _MhcFunction *function_ptr,
			const float time, const u32 key_search_hint,
			const u32 number_of_elements,
			float *value_array, float *differential_array );

typedef struct _MhcFunction
{
    _msoDeriveFrom( MhcNode );
    u32				number_of_keys;
    float			*time_array;
    float			*key_data;
    u32				continuity;
    float			junction;
    MhcFunctionGetValueFunc	get_value;
} MhcFunction;

/* Declare Functions */
extern u32 mhcConstFunctionGetValue(
			MhcFunction *function_ptr,
			const float time, const u32 key_search_hint,
			const u32 number_of_elements,
			float *value_array, float *differential_array );
extern u32 mhcLinearFunctionGetValue(
			MhcFunction *function_ptr,
			const float time, const u32 key_search_hint,
			const u32 number_of_elements,
			float *value_array, float *differential_array );
extern u32 mhcHermiteFunctionGetValue(
			MhcFunction *function_ptr,
			const float time, const u32 key_search_hint,
			const u32 number_of_elements,
			float *value_array, float *differential_array );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mhc_Function_h */
