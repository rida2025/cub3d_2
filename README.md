guide to our cub3d

put_map->
Starting column is alway 0
ray_angle = player angle - (field of view / 2)
Then we start casting rays
Each ray we cast we increase the column because in each ray we draw the entire rows in that column
And we increase the ray_angle by field of view / by num_rays which will result on the ray to hit every column

RAY_CASTING->
Normalize the ray_angle so its never outside the range of 360
Now calculate the horizontal interception
We call

HORIZONTAL_HELPER->
We give its he ray angle and our player position and it find the first horizontal interception by finding its x and y
The interception_Y = the player_Y / by the sizeOfsquire then we floor it to get the upper position in map and we * 32 to get the exact location of the horizontal_Y
But if the player was looking dawn we need to increase 32 in the Y so its the squire under him

Now we need to find the horizontal_x interception we can do that by this:
Which is player_x + ((the interception_y we already find - player_y) / tan(ray_angle))

Now I calculate the xstep and ystep to get to the next horizontal intercept
The y step for the horizontal	is the squire size so its 32 but if the player is facing up that it has to be -32
And for the step its:
ystep / tan(ray_angle)
And if the player is facing right and the value is positive or if the player is facing left and the step value is negative change the sign of the xstep
And set the horizontal flag to 0