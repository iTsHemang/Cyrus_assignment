This project is made with Unreal Engine version 5.6.0, and all the features are made only using C++.

BoxSpawner: 
  - Box Spawner will load A JSON file containing box types and objects data. 
  - Randomly select a type and transform data.
  - Spawns a box with selected parameters. 

Box: 
  - The box will contain data like name, health, and score.
  - On a projectile hit, it will take 1 damage. 
  - If health reaches zero, it destroys itself and notifies the UI with its score and type 

Player Character: 
  - On fire input (mouse left click) spawns a projectile at the rifle’s muzzle location. 

Projectile: 
  - Uses Unreal's projectile system to travel.
  - On collision with the box, it will deal 1 damage to the box.

UserWidget: 
 - Updates and displays the total score.
 - Additionally, it will display the last destroyed box type.

Challenges:
 - One of the trickiest parts was to load and fetch data from a JSON file. And as suggested, I took help from the internet.
 - The other tricky part was detecting a collision. Because the  box does not have physics, the projectile was not detecting the collision with the box. But it was a simple fix.

To test the feature, just play it on the editor. The player character will be equipped with a rifle, and the first box will spawn automatically. Mouse left click to fire. As soon as the box is destroyed, another will spawn, and the score will update.

Here's the YouTube link to the video showcasing my final project: https://youtu.be/5pNZSaQ_pDU
