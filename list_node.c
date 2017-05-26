/**
  ************************************************************************************************************************************
  * File Name          : list.h
  * Description        : This file provides structural definitions of various components and conventions that have been devised 
  *                       to together form Menu Definition Language.
  *              
  ************************************************************************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "linked_list.h"

/* USER CODE BEGIN 0 */


//
// node.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

/*
 * Allocates a new list_node_t. NULL on failure.
 */

list_node_t *
list_node_new(void *val) {
  list_node_t *self;
  if (!(self = LIST_MALLOC(sizeof(list_node_t))))
    return NULL;
  self->prev = NULL;
  self->next = NULL;
  self->val = val;
  return self;
}




/* USER CODE END 0 */


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

