// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "fdf.h"

static mlx_image_t* image;

// -----------------------------------------------------------------------------
/* ----- */
#include <stdlib.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "animate.h"

#define WIDTH 640
#define HEIGHT 360

typedef struct s_color_game {
  mlx_t * mlx;
  mlx_image_t * menu_bg;
  t_animation * select_animation;
} t_color_game;

void error(void) {
  puts(mlx_strerror(mlx_errno));
  exit(EXIT_FAILURE);
}

void bait(void*ptr){(void)ptr;};

t_color_game init_game() {
  mlx_t*          mlx;
  mlx_texture_t*  texture;
  mlx_image_t*    img;
  t_animation*    anim;
  t_sprite        sprite;

  // Start mlx
  mlx = mlx_init(WIDTH, HEIGHT, "Color Game", false);
  if (!mlx)
    error();
  // Try to load the file
  texture = mlx_load_png("./images/menu_bg.png");
  if (!texture)
    error();
  // Convert texture to a displayable image
  img = mlx_texture_to_image(mlx, texture);
  if (!img)
    error();
  mlx_delete_texture(texture);
  // Sprite & Animation
  sprite = new_sprite("./images/select_sprite_sheet.png", mlx);
  anim = slice_sprite(&sprite, (sprite_slice){0, 0, 128, 32, 0, 0}, false, 5, 120);
  destroy_sprite(&sprite);

  return (t_color_game){mlx, img, anim};
}

int32_t main(void)
{
  t_color_game cg;

  cg = init_game();

  if (mlx_image_to_window(cg.mlx, cg.menu_bg, 0, 0) == -1)
    error();

  mlx_loop(cg.mlx);

  ft_lstclear(&cg.select_animation->frames, bait);
  free(cg.select_animation);
  mlx_terminate(cg.mlx);
  return (EXIT_SUCCESS);
}
/* ----- */

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t *mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
