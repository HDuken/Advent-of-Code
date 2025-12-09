def rectangle_area(t1, t2):
    x1, y1 = t1
    x_2, y_2 = t2
    return (abs(x_2 - x1) + 1) * (abs(y_2 - y1) + 1)


vertical_segments = []
horizontal_segments = []


def add_line(t1, t2):
    x1, y1 = t1
    x2, y2 = t2

    if x1 == x2:
        if y1 > y2:
            y1, y2 = y2, y1
        vertical_segments.append((x1, y1, y2))
    else:
        if x1 > x2:
            x1, x2 = x2, x1
        horizontal_segments.append((y1, x1, x2))


def horizontal_ray_intersects_vertical(px, py, vx, vy1, vy2):
    # Check if the horizontal ray at y=py intersects the vertical segment
    # Segment is at x=vx and spans vy1..vy2 (with vy1 < vy2)

    # Ray crosses only if point's y is within [vy1, vy2)
    if not (vy1 <= py < vy2):
        return False

    # The ray is to the right, so we need px <= vx
    if px > vx:
        return False

    return True


def seg_intersect_hv(y, x1, x2, x, y1, y2):
    # horizontal segment: y, x1..x2
    # vertical segment:   x, y1..y2
    return (x1 < x < x2) and (y1 < y < y2)


def is_inside_contour(p):
    px, py = p

    if p in boundary:
        return True

    cnt = 0
    # Count intersections with vertical edges
    for vx, vy1, vy2 in vertical_segments:
        if horizontal_ray_intersects_vertical(px, py, vx, vy1, vy2):
            cnt += 1

    return (cnt % 2) == 1


def rect_edges(c1, c2):
    x1, y1 = c1
    x2, y2 = c2
    return [
        ("H", y1, min(x1, x2), max(x1, x2)),  # top
        ("H", y2, min(x1, x2), max(x1, x2)),  # bottom
        ("V", x1, min(y1, y2), max(y1, y2)),  # left
        ("V", x2, min(y1, y2), max(y1, y2)),  # right
    ]


def rect_corners(c1, c2):
    x1, y1 = c1
    x2, y2 = c2
    return [c1, (x1, y2), c2, (x2, y1)]


def is_valid_rectangle(c1, c2):
    # All corners must be inside or on the boundary.
    for corner in rect_corners(c1, c2):
        if corner not in red_tiles and not is_inside_contour(corner):
            return False

    # Rectangle must not intersect the contour boundary.
    for kind, a, b1, b2 in rect_edges(c1, c2):
        for kind, a, b1, b2 in rect_edges(c1, c2):
            if kind == "H":
                y = a
                x1 = b1
                x2 = b2
                for vx, vy1, vy2 in vertical_segments:
                    if seg_intersect_hv(y, x1, x2, vx, vy1, vy2):
                        return False
            else:
                x = a
                y1 = b1
                y2 = b2
                for hy, hx1, hx2 in horizontal_segments:
                    if seg_intersect_hv(hy, hx1, hx2, x, y1, y2):
                        return False

    return True


boundary = set()


def fill_boundary(old, new):
    x1, y1 = old
    x2, y2 = new

    dx = 0 if x1 == x2 else (1 if x2 > x1 else -1)
    dy = 0 if y1 == y2 else (1 if y2 > y1 else -1)

    x, y = x1, y1
    boundary.add((x, y))
    while (x, y) != (x2, y2):
        x += dx
        y += dy
        boundary.add((x, y))


red_tiles = []
with open("9.txt", "r") as f:
    for line in f.readlines():
        tile_coordinates = tuple(map(int, line.strip().split(",")))
        if len(red_tiles) > 0:
            add_line(red_tiles[-1], tile_coordinates)
            fill_boundary(red_tiles[-1], tile_coordinates)
        red_tiles.append(tile_coordinates)
    add_line(red_tiles[-1], red_tiles[0])
    fill_boundary(red_tiles[-1], red_tiles[0])

max_area = 0
for i in range(len(red_tiles)):
    for j in range(i + 1, len(red_tiles)):
        if is_valid_rectangle(red_tiles[i], red_tiles[j]):
            max_area = max(max_area, rectangle_area(
                red_tiles[i], red_tiles[j]))
print(max_area)
