#include "cub3D.h"
#define MAX_VALUE 2147483647

double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int mapHasWallAt(t_game * data, double x, double y)
{
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return TRUE;
    }
	// printf("Passou\n");
    int mapGridIndexX = (int)(floor(x / data->map.map_tile_size.x));
    int mapGridIndexY = (int)(floor(y / data->map.map_tile_size.x));
	
	// printf("MAPA POS: %c | x: %f - y: %f\n", data->map.map_temp[mapGridIndexY][mapGridIndexX], x, y);
	// printf("x: %d - y: %d - colmap %d - rowmap %d - MAP %c | ", mapGridIndexX, mapGridIndexY, data->map.col_map / (int)data->map.map_tile_size.x, data->map.row_map / (int)data->map.map_tile_size.x, data->map.map_temp[mapGridIndexY][mapGridIndexX]);
	// if(mapGridIndexX >= data->map.col_map / (int)data->map.map_tile_size.x)
	// 	mapGridIndexX = data->map.col_map / (int)data->map.map_tile_size.x - 1;
	// if(mapGridIndexY >= data->map.row_map / (int)data->map.map_tile_size.x)
	// 	mapGridIndexY = data->map.row_map / (int)data->map.map_tile_size.x - 1;
	// printf("mapGridIndexX: %d - mapGridIndexY: %d - coluna: %f - linha: %f\n", mapGridIndexX, mapGridIndexY, data->map.col_map / data->map.map_tile_size.x, data->map.row_map / data->map.map_tile_size.x);
	if(data->map.map_temp[mapGridIndexY][mapGridIndexX] =='1')
	{
		// printf("MAPA POS: %c\n", data->map.map_temp[mapGridIndexY][mapGridIndexX]);
		// printf("Intersect\n\n");
		return 1;
	}
	else
	{
		// printf("MAPA POS: %c\n", data->map.map_temp[mapGridIndexY][mapGridIndexX]);
		// printf("NOT Intersect\n\n");
		return 0;
	}
}

double normalizeAngle(double angle)
{
    angle = remainder(angle, M_PI * 2);
    if (angle < 0)
        angle = (M_PI * 2) + angle;
    return angle;
}

void castRay(t_game *data, int px, int py, double rayAngle)
{
        rayAngle = normalizeAngle(rayAngle);
        double wallHitX = 0;
        double wallHitY = 0;

		int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
		int isRayFacingUp = !isRayFacingDown;

		int isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
		int isRayFacingLeft = !isRayFacingRight;

        double xintercept, yintercept;
        double xstep, ystep;

	///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = FALSE;
    double horzWallHitX = 0;
    double horzWallHitY = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor((double)py / data->map.map_tile_size.x) * data->map.map_tile_size.x;
    yintercept += isRayFacingDown ? data->map.map_tile_size.x : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = px + (yintercept - py) / tan(rayAngle);

    ystep = data->map.map_tile_size.x;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = data->map.map_tile_size.x / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;

    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	if(ystep > (double)data->map.row_map * data->map.map_tile_size.x)
		ystep = (double)data->map.row_map;
	if(xstep > (double)data->map.col_map * data->map.map_tile_size.x)
		xstep = (double)data->map.col_map;

    double nextHorzTouchX = xintercept;
    double nextHorzTouchY = yintercept;

	if(isRayFacingUp)
		nextHorzTouchY--;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= (data->map.map_tile_size.x * (double)data->map.col_map) && nextHorzTouchY >= 0 && nextHorzTouchY <= (data->map.map_tile_size.x * (double)data->map.row_map)) {
        double xToCheck = nextHorzTouchX;
        double yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
		// printf("xToCheck: %f - yToCheck: %f\n", xToCheck, yToCheck);
        if (mapHasWallAt(data, xToCheck, yToCheck)) {
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            foundHorzWallHit = TRUE;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
	
	// drawLine(data, px, py, horzWallHitX, horzWallHitY, 0x00000000);


	// ///////////////////////////////////////////
    // // VERTICAL RAY-GRID INTERSECTION CODE
    // ///////////////////////////////////////////

    int foundVertWallHit = FALSE;
    double vertWallHitX = 0;
    double vertWallHitY = 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = floor((double)px / data->map.map_tile_size.x) * data->map.map_tile_size.x;
    xintercept += isRayFacingRight ? data->map.map_tile_size.x : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = (double)py + (xintercept - (double)px) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    xstep = data->map.map_tile_size.x;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = data->map.map_tile_size.x * tan(rayAngle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

	if(ystep > (double)data->map.row_map * data->map.map_tile_size.x)
		ystep = (double)data->map.row_map;
	if(xstep > (double)data->map.col_map * data->map.map_tile_size.x)
		xstep = (double)data->map.col_map;

    double nextVertTouchX = xintercept;
    double nextVertTouchY = yintercept;

	if(isRayFacingLeft)
		nextVertTouchX--;
    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= (data->map.map_tile_size.x * (double)data->map.col_map) && nextVertTouchY >= 0 && nextVertTouchY <= (data->map.map_tile_size.x * (double)data->map.row_map)) {
        double xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        double yToCheck = nextVertTouchY;
        if (mapHasWallAt(data, xToCheck, yToCheck)) {
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            foundVertWallHit = TRUE;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

        // Calculate both horizontal and vertical distances and choose the smallest value
        double horzHitDistance = (foundHorzWallHit)
            ? distanceBetweenPoints((double)px, (double)py, horzWallHitX, horzWallHitY)
            : MAX_VALUE;
        double vertHitDistance = (foundVertWallHit)
            ? distanceBetweenPoints((double)px, (double)py, vertWallHitX, vertWallHitY)
            : MAX_VALUE;

		// // only store the smallest of the distances
        wallHitX = (horzHitDistance < vertHitDistance) ? horzWallHitX : vertWallHitX;
        wallHitY = (horzHitDistance < vertHitDistance) ? horzWallHitY : vertWallHitY;
		// // printf("px: %d - py: %d - wallHitX: %f - wallHitY: %f\n", px, py, wallHitX, wallHitY);
        // distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
        // wasHitVertical = (vertHitDistance < horzHitDistance);
		// double correct_distance = distance * cos(rayAngle - data->player.rotationAngle);
		// double distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		// double wall = (data->map.map_tile_size.x / correct_distance) * distanceProjPlane;
		drawLine(data, (px+1) + data->map.map_tile_size.x, (py+1) + data->map.map_tile_size.x, (int)wallHitX + data->map.map_tile_size.x, (int)wallHitY + data->map.map_tile_size.x, 0x00000000);
}

