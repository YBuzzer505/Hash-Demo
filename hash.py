def hex_digit_to_int(c: str) -> int:
    """Convert a single hex digit (0-F) to int."""
    if c.isdigit():
        return int(c)
    return 10 + ord(c.upper()) - ord('A')


def main():
    password = input("Enter your password: ")

    # Convert password to hex string
    hex_str = "".join(f"{ord(ch):02X}" for ch in password)
    print("Password in hex:", hex_str)

    # some Ai (GPT)
    
    # Each 3 hex digits = 1 pixel
    num_pixels = (len(hex_str) + 2) // 3  # round up
    width = num_pixels
    height = 1

    with open("password.ppm", "w") as f:
        # PPM header
        f.write(f"P3\n{width} {height}\n255\n")

        # Process hex string in chunks of 3
        for i in range(0, len(hex_str), 3):
            h1 = hex_str[i]
            h2 = hex_str[i + 1] if i + 1 < len(hex_str) else "0"
            h3 = hex_str[i + 2] if i + 2 < len(hex_str) else "0"

            r = hex_digit_to_int(h1) * 16
            g = hex_digit_to_int(h2) * 16
            b = hex_digit_to_int(h3) * 16

            f.write(f"{r} {g} {b} ")

        f.write("\n")

    print("Image saved as password.ppm")


if __name__ == "__main__":
    main()
