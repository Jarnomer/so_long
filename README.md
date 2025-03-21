<h1 align="center">
  <img src="assets/so_long.png" alt="so_long" width="400">
</h1>

<p align="center">
	<b><i>Simple skeleton themed 2D game 🎮 featuring mlx42.</i></b><br>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Score-125%2F100-lightgreen?style=for-the-badge" alt="score">
  <img src="https://img.shields.io/github/languages/top/Jarnomer/so_long?style=for-the-badge&logo=c&label=%20&labelColor=gray&color=lightblue" alt="GitHub top language">
	<img src="https://img.shields.io/github/languages/code-size/Jarnomer/so_long?style=for-the-badge&color=lightyellow" alt="GitHub code size in bytes">
  <img src="https://img.shields.io/github/directory-file-count/Jarnomer/so_long/sources?style=for-the-badge&label=sources&color=pink" alt="GitHub repo file or directory count (in path)">
</p>

<p align="center">
    <img src="https://img.shields.io/badge/Type-Solo-violet?style=for-the-badge" alt="type">
  <img src="https://img.shields.io/github/last-commit/Jarnomer/so_long/main?style=for-the-badge&color=red" alt="GitHub last commit (branch)">
</p>

<div align="center">

## Table of Contents

[📝 General](#-general)
[🛠️ Build](#️-build)
[⚡ Usage](#-usage)
[🚀 Details](#-details)
[♻️ Resources](#️-resources)

</div>

## 📝 General

Goal of the project is to create simple 2D video game.

It uses `map` files with predefined limitations to genarate the game world.

World is build in `128x128` cells and textures are `compressed` if map dimensions exceed screen size.

Features [mlx42](https://github.com/codam-coding-college/MLX42) to draw graphics and register keystrokes.

## 🛠️ Build

GNU `make` and `gcc` are required to build and compile the project.

You also need to install [mlx42](https://github.com/codam-coding-college/MLX42) and all its prerequisites.

⚠️ Game was designed for `linux`. Extra steps might be required for MacOS and Windows. ⚠️

```bash
git clone --recurse-submodules https://github.com/Jarnomer/so_long.git so_long
```

```bash
cd so_long && make all
```

## ⚡ Usage

You can run the game by giving it a map file. Invalid argument or map results into `error`.

```bash
./so_solong maps/<map_name>.ber
```

You can `move` around with `WASD` keys and `ESC` will close the game.

Goal is to `collect` all gems and then `escape` through exit with least amount of moves.

Be careful! If you take your time the `enemies` start to `multiple`.

## 🚀 Details

After initialization, `open_map` validates the file and `read_map` checks for map artifacts.

```c
static void read_file(t_mapinfo *map, t_solong *game)
{
  while (true)
  {
    map->buff = get_next_line(map->fd);
    if (!map->buff)
      break ;
    if (*map->buff == '\n')
      error_exit(ERR_MAP, MSG_LINE, game);
    map->temp = ft_strjoin(map->read, map->buff);
    if (!map->temp)
      error_exit(ERR_MEM, MSG_MEM, game);
    free(map->read);
    map->read = map->temp;
    free(map->buff);
  }
  if (!*map->read)
    error_exit(ERR_MAP, MSG_EMPTY, game);
  else if (map->read[ft_strlen(map->read) - 1] == '\n')
    error_exit(ERR_MAP, MSG_LINE, game);
}
```

Then `test_map` uses `floodfill` to make sure all pickups are collectable and exit is reachable.

```c
static void clear_pickups(char **duplex, int x, int y)
{
  static const char *pickup_or_floor = "0C";
  static const char pickup_mark = 'X';

  duplex[y][x] = pickup_mark;
  if (ft_strchr(pickup_or_floor, duplex[y + 1][x]))
    clear_pickups(duplex, x, y + 1);
  if (ft_strchr(pickup_or_floor, duplex[y - 1][x]))
    clear_pickups(duplex, x, y - 1);
  if (ft_strchr(pickup_or_floor, duplex[y][x + 1]))
    clear_pickups(duplex, x + 1, y);
  if (ft_strchr(pickup_or_floor, duplex[y][x - 1]))
    clear_pickups(duplex, x - 1, y);
  return ;
}
```

Once map is verified, `assests` are loaded and drawn to mlx window for `play_game` to apply hooks.

```c
void load_assets(t_solong *game)
{
  int width;
  int height;

  width = CELL_SIZE * game->map->width;
  height = CELL_SIZE * game->map->height;
  game->mlx = mlx_init(width, height, "so_long", false);
  if (!game->mlx)
    error_exit(ERR_MLX, MSG_MLX, game);
  mlx_get_monitor_size(0, &game->screen_width, &game->screen_height);
  if (width > game->screen_width || height > game->screen_height)
    alter_window_settings(game->map, game);
  load_textures(game);
}
```

```c
void play_game(t_solong *game)
{
  mlx_close_hook(game->mlx, &close_window, game);
  mlx_key_hook(game->mlx, &control_keys, game);
  mlx_loop_hook(game->mlx, animate_player, game);
  mlx_loop_hook(game->mlx, move_enemies, game);
  mlx_loop(game->mlx);
}
```

## ♻️ Resources

[mlx42](https://github.com/codam-coding-college/MLX42) main API used for GLFW and OpenGL functionatilies.

[itch.io](https://itch.io/game-assets/free/tag-sprites) great place to find sprites and other game assets.

[solong-error-tester](https://github.com/Jarnomer/solong-error-tester) personal unit tester for error handling.

## 4️⃣2️⃣ Footer

For my other 42 projects and general information, please refer the [Hive42](https://github.com/Jarnomer/Hive42) page.

I have also created error handling [unit testers](https://github.com/Jarnomer/42Testers) for `pipex`, `so_long` and `cub3D`.

### Cheers and good luck! 🥳
