## Explication

# Direction des rayons
    --> Pour chaque colonne de lécran, on calcule un vecteur direction du rayon :
        rayDir=(dirX+planeX⋅cameraX,dirY+planeY⋅cameraX)

# Recherche d'intersection avec les murs
    --> On utilise l algorithme DDA (Digital Differential Analyzer) pour trouver l intersection du rayon avec les murs de la carte.
    --> On calcule les distances initiales aux prochaines intersections de grille en x et y (sideDistX, sideDistY).
    --> On calcule les distances entre les intersections successives en x et y (deltaDistX, deltaDistY).
    --> On détermine la direction de pas (stepX, stepY) en fonction du signe de rayDirX et rayDirY.
    --> On effectue une boucle DDA jusqu à ce qu on trouve un mur (mapX, mapY) où la valeur dans la carte est 1.
    --> On détermine si l intersection a été faite en x ou en y (side) 
    
    En avançant pas à pas dans la grille (algorithme DDA), on détermine la première case "mur" que le rayon touche.

# Distance au mur / joueur + correction

    (Pour eviter l effet de fish eye) --> On calcule la distance perpendiculaire
    
# Appliquer Thales pour calculer la hauteur percue du mur

# Determiner les couleurs des murs du plafonds et du sol


/////// ////////

--> Boucle principale / rafraîchit l’image
int render(t_game *game)
{
    clear_image(game->mlx, 0x003366);  // couleur du fond (plafond + sol provisoire)
 handle_movement(game)
    cast_all_rays(game);               // lancer les rayons pour dessiner les murs
    mlx_put_image_to_window(game->mlx->mlx_init, game->mlx->mlx_win, game->mlx->img_ptr, 0, 0);
    return (0);
}

--> Shoot Ray / parcourt chaque colonne
void cast_all_rays(t_game *game)
{
    int x = 0;

    while (x < WIDTH)
    {
        cast_ray(game, x);
        x++;
    }
}

void cast_ray(t_game *game, int x)// s’occupe d’un rayon (init → DDA → distance → projection)
{
    t_ray ray;

    init_ray(&ray, game, x);        // 1. calculer la direction du rayon
    perform_dda(&ray, game);        // 2. avancer dans la map jusqu’au mur
    compute_distance(&ray, game);   // 3. calculer distance perpendiculaire
    draw_wall(&ray, game, x);       // 4. projeter le mur et dessiner la colonne
}

--> initialisation des rayons
void init_ray(t_ray *ray, t_game *game, int x)
{
    double cameraX = 2 * x / (double)WIDTH - 1;

    ray->dirX = game->dirX + game->planeX * cameraX;
    ray->dirY = game->dirY + game->planeY * cameraX;
    ray->mapX = (int)game->posX;
    ray->mapY = (int)game->posY;

    ray->deltaDistX = fabs(1 / ray->dirX);
    ray->deltaDistY = fabs(1 / ray->dirY);

    init_step(ray, game); // calcule stepX/stepY et sideDistX/sideDistY
}



init_step() is the helper function that prepares two critical things for the DDA (Digital Differential Analyzer) raycasting loop:

stepX / stepY → direction to step in the grid (-1 or +1) depending on the sign of the ray direction.

sideDistX / sideDistY → initial distance from the player position to the first grid boundary along X and Y.



void init_step(t_ray *ray, t_game *game)
{
    // X direction
    if (ray->dirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (game->posX - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - game->posX) * ray->deltaDistX;
    }

    // Y direction
    if (ray->dirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (game->posY - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - game->posY) * ray->deltaDistY;
    }
}


--> DDA
void perform_dda(t_ray *ray, t_game *game)
{
    int hit = 0;

    while (hit == 0)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
      if (game->map[ray->mapY][ray->mapX] == '1')
            hit = 1;
    }
}

--> distance perpendiculaire
void compute_distance(t_ray *ray, t_game *game)
{
    if (ray->side == 0)
        ray->perpWallDist = (ray->mapX - game->posX + (1 - ray->stepX) / 2) / ray->dirX;
    else
        ray->perpWallDist = (ray->mapY - game->posY + (1 - ray->stepY) / 2) / ray->dirY;
}

--> Projection + dessin 
void draw_wall(t_ray *ray, t_game *game, int x)// trace la colonne
{
    int lineHeight = (int)(HEIGHT / ray->perpWallDist);

    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0) drawStart = 0;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

    int color = (ray->side == 1) ? 0xAAAAAA : 0xFFFFFF; // simple shading
    draw_vertical_line(game->mlx, x, drawStart, drawEnd, color);
}

--> Dessin de pixels/colonnes
void draw_vertical_line(t_mlx *mlx, int x, int y_start, int y_end, int color)
{
    int y = y_start;
    while (y <= y_end)
    {
        char *px = mlx->addr + (y * mlx->line_len + x * (mlx->img_bpp / 8));
        *(unsigned int *)px = color;
        y++;
    }
}



Then the next essential pieces are:

Movement (handle_movement)

Ceiling/floor colors

Parsing .cub

Textures


--- Mouvement ----
void move_forward(t_game *game)

void move_backward(t_game *game)

void strafe_left(t_game *game)


void strafe_right(t_game *game)


void rotate_left(t_game *game)

void rotate_right(t_game *game)

void handle_movement(t_game *game)
{
    double moveSpeed = 0.1;   // adjust for desired speed
    double rotSpeed  = 0.05;  // rotation speed in radians

    double newX, newY;

    // --- Forward / Backward ---
    if (game->keys.w)
    {
        newX = game->player.posX + game->player.dirX * moveSpeed;
        newY = game->player.posY + game->player.dirY * moveSpeed;
        if (game->map[(int)game->player.posY][(int)newX] == '0') 
            game->player.posX = newX;
        if (game->map[(int)newY][(int)game->player.posX] == '0') 
            game->player.posY = newY;
    }
    if (game->keys.s)
    {
        newX = game->player.posX - game->player.dirX * moveSpeed;
        newY = game->player.posY - game->player.dirY * moveSpeed;
        if (game->map[(int)game->player.posY][(int)newX] == '0') 
            game->player.posX = newX;
        if (game->map[(int)newY][(int)game->player.posX] == '0') 
            game->player.posY = newY;
    }

    // --- Strafe left / right ---
    if (game->keys.a)
    {
        newX = game->player.posX - game->player.planeX * moveSpeed;
        newY = game->player.posY - game->player.planeY * moveSpeed;
        if (game->map[(int)game->player.posY][(int)newX] == '0') 
            game->player.posX = newX;
        if (game->map[(int)newY][(int)game->player.posX] == '0') 
            game->player.posY = newY;
    }
    if (game->keys.d)
    {
        newX = game->player.posX + game->player.planeX * moveSpeed;
        newY = game->player.posY + game->player.planeY * moveSpeed;
        if (game->map[(int)game->player.posY][(int)newX] == '0') 
            game->player.posX = newX;
        if (game->map[(int)newY][(int)game->player.posX] == '0') 
            game->player.posY = newY;
    }

    // --- Rotate Left / Right ---
    if (game->keys.left || game->keys.right)
    {
        double oldDirX = game->player.dirX;
        double oldPlaneX = game->player.planeX;
        double angle = (game->keys.left ? rotSpeed : -rotSpeed);

        // Rotate direction vector
        game->player.dirX = game->player.dirX * cos(angle) - game->player.dirY * sin(angle);
        game->player.dirY = oldDirX * sin(angle) + game->player.dirY * cos(angle);

        // Rotate camera plane
        game->player.planeX = game->player.planeX * cos(angle) - game->player.planeY * sin(angle);
        game->player.planeY = oldPlaneX * sin(angle) + game->player.planeY * cos(angle);
    }
}



------ INIT -----

#include "init_structs.h"

void init_game_struct(t_game *game)
{
    game->mlx = NULL;
    game->map = NULL;
    game->map_w = 0;
    game->map_h = 0;
    game->player_x = -1;
    game->player_y = -1;
    game->player_dir = 'N';
    game->tex_no = NULL;
    game->tex_so = NULL;
    game->tex_we = NULL;
    game->tex_ea = NULL;
    game->floor_rgb = -1;
    game->ceil_rgb = -1;

    // Initialisation du joueur
    init_player(game);
}

void init_player(t_game *game)
{
    game->player.posX = (double)game->player_x + 0.5;
    game->player.posY = (double)game->player_y + 0.5;

    if (game->player_dir == 'N') {
        game->player.dirX = -1;
        game->player.dirY = 0;
        game->player.planeX = 0;
        game->player.planeY = 0.66;
    }
    else if (game->player_dir == 'S') {
        game->player.dirX = 1;
        game->player.dirY = 0;
        game->player.planeX = 0;
        game->player.planeY = -0.66;
    }
    else if (game->player_dir == 'E') {
        game->player.dirX = 0;
        game->player.dirY = 1;
        game->player.planeX = 0.66;
        game->player.planeY = 0;
    }
    else if (game->player_dir == 'W') {
        game->player.dirX = 0;
        game->player.dirY = -1;
        game->player.planeX = -0.66;
        game->player.planeY = 0;
    }
}

void init_textures(t_game *game)
{
    // Ici tu pourrais charger tes textures depuis les fichiers .xpm
    // ou juste stocker les chemins pour l'instant
    game->tex_no = strdup(game->tex_no);
    game->tex_so = strdup(game->tex_so);
    game->tex_we = strdup(game->tex_we);
    game->tex_ea = strdup(game->tex_ea);
}

void init_colors(t_game *game)
{
    // Exemple si tu as déjà des valeurs RGB dans le parsing
    game->floor_rgb = game->floor_rgb;
    game->ceil_rgb = game->ceil_rgb;
}

