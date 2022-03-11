/*
 * Colors.h
 *
 *  Created on: Nov 22, 2017
 *      Author: tr_dawson
 */

#ifndef COLORS_H_
#define COLORS_H_

#define DEFAULT_MASK        (true)
#define PIXEL_ALPHA         0xFF000000
#define PIXEL_RED           0x00FF0000
#define PIXEL_GREEN         0x0000FF00
#define PIXEL_BLUE          0x000000FF
#define PIXEL_GRAY          0x00808080
#define PIXEL_PURPLE        (PIXEL_RED|PIXEL_BLUE)
#define PIXEL_WHITE         0x00FFFFFF
#define PIXEL_BLACK         0x00000000
#define PIXEL_BLANK         PIXEL_BLACK
#define PIXEL_GOLD          (PIXEL_RED>>1)
#define PIXEL_RED_PART(color)   ((color)&PIXEL_RED)
#define PIXEL_BLUE_PART(color)  ((color)&PIXEL_BLUE)
#define PIXEL_GREEN_PART(color) ((color)&PIXEL_GREEN)
#define PIXEL_DARK(color)       ((PIXEL_RED_PART  (PIXEL_RED_PART(color)  /2)) | \
                                 (PIXEL_GREEN_PART(PIXEL_GREEN_PART(color)/2)) | \
                                 (PIXEL_BLUE_PART (PIXEL_BLUE_PART(color) /2)))
#define PIXEL_DARKER(color)     ((PIXEL_RED_PART  (PIXEL_RED_PART(color)  /4)) | \
                                 (PIXEL_GREEN_PART(PIXEL_GREEN_PART(color)/4)) | \
                                 (PIXEL_BLUE_PART (PIXEL_BLUE_PART(color) /4)))
#define PIXEL_LIGHT(color)      ((PIXEL_RED_PART  ((PIXEL_RED_PART(color)  +PIXEL_RED)      /2)) | \
                                 (PIXEL_GREEN_PART((PIXEL_GREEN_PART(color)+PIXEL_GREEN)    /2)) | \
                                 (PIXEL_BLUE_PART ((PIXEL_BLUE_PART(color) +PIXEL_BLUE)     /2)))
#define PIXEL_LIGHTER(color)    ((PIXEL_RED_PART  ((PIXEL_RED_PART(color)  +(PIXEL_RED*3))  /4)) | \
                                 (PIXEL_GREEN_PART((PIXEL_GREEN_PART(color)+(PIXEL_GREEN*3))/4)) | \
                                 (PIXEL_BLUE_PART ((PIXEL_BLUE_PART(color) +(PIXEL_BLUE*3)) /4)))
#define PIXEL_LIGHTEN(color, nom, denum) ((PIXEL_RED_PART  ((PIXEL_RED_PART(color)   * (nom)) / (denum))) | \
                                          (PIXEL_GREEN_PART((PIXEL_GREEN_PART(color) * (nom)) / (denum))) | \
                                          (PIXEL_BLUE_PART ((PIXEL_BLUE_PART(color)  * (nom)) / (denum))))

#endif /* COLORS_H_ */
