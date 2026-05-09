README PART2

 212097117 אופיר שוקרון
207511130 סניטה גסנוב

Explosion Effect: The bomb destroys Walls ('w') and damages Players within range.
  (*Note: Immutable walls or other items are NOT affected by the explosion in this version).

Disposing Items: (Backwards Logic):
 When pressing the Dispose key (E for Player 1, O for Player 2), the item is NOT dropped in front of the player.
Instead, the item is dropped at the player's *previous position*.
- Example: If you move RIGHT and then press Dispose, the bomb/item will be placed to your LEFT (behind you).

Level Structure & Doors:  Single Door Rule: Each room (level) contains exactly one door leading to the next stage.

Level Files: The game loads levels from 'adv-world_XX.screen.txt'.
The logic supports dynamic updates of the single door based on the file data.

Born Point Players + Legend - The Legend is placed dynamically based on the L location. Since player positions are defined in the source text files, care must be taken to prevent the Legend from rendering over the players' spawn locations. 
	If L located in the middle of line - we consider it as start point.

Score - We calculate score by adding 1 when answering riddle correctly.