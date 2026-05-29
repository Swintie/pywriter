from argparse import ArgumentParser
from time import sleep


def main(filename, speed):
    with open(filename, "r", encoding="utf-8") as f:  # Open file and read
        text = f.read()
        print("\033[H\033[J", end="")
    for char in text:  # Print text
        print(char, end="", flush=True)
        sleep(speed)


if __name__ == "__main__":
    try:
        parser = ArgumentParser()
        parser.add_argument(
            "-s",
            "--speed",
            type=float,
            default=0.1,
            help="Set the speed of typing. (lower is faster)",
        )
        parser.add_argument("filename")
        args = parser.parse_args()
        main(args.filename, speed=args.speed)
    except KeyboardInterrupt:
        pass
    except Exception as e:
        print(f"\n{e}")
