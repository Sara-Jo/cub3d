/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjo <sjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:30:57 by sjo               #+#    #+#             */
/*   Updated: 2022/12/11 23:48:12 by sjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define width 640
#define height 480
#define texWidth 64
#define texHeight 64
#define X_EVENT_KEY_PRESS 2
#define X_EVENT_KEY_EXIT 17

typedef struct s_img
{
    void *img;
    int *data;
    int size_l;
    int bpp;
    int endian;
    int img_width;
    int img_height;
} t_img;

typedef struct s_info
{
    // char *texture_no;
    // char *texture_we;
    // char *texture_ea;
    // char *texture_so;
    int **texture;
    int f_color;
    int c_color;
    char **map;
    int map_width;
    int map_height;
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    void *mlx;
    void *win;
    t_img img;
    double moveSpeed;
    double rotSpeed;
    int buf[height][width];
} t_info;