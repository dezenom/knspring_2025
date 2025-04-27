from PIL import Image
import os

inp = "res/scenes/game/0.png"
outp = "res/scenes/environment"
tile_width = 3200
tile_height = 3200

os.makedirs(outp, exist_ok=True)

image = Image.open(inp)
image_width, image_height = image.size

cols = (image_width + tile_width - 1) // tile_width
rows = (image_height + tile_height - 1) // tile_height

print(f"Splitting into {rows} rows x {cols} columns...")

for row in range(rows):
    for col in range(cols):
        left = col * tile_width
        upper = row * tile_height
        right = min(left + tile_width, image_width)
        lower = min(upper + tile_height, image_height)

        box = (left, upper, right, lower)
        tile = image.crop(box)

        tile_filename = f"{col}.png"
        tile_path = os.path.join(outp, tile_filename)
        tile.save(tile_path)
        print(f"Saved {tile_filename}")

print("Done splitting!")
