import asyncio

async def factorial(name: str, number: int) -> int:
    product = 1 if number > 0 else 0
    for i in range(1, number + 1):
        product *= i
        print(f"Task {name}: Compute factorial({number}), currently i={i}...")
        await asyncio.sleep(1)
    print(f"Task {name}: factorial({number}) = {product}")
    return product

async def main():
    print(await asyncio.gather(
        factorial("A", 3),
        factorial("B", 4),
        factorial("C", 5)
    ))

asyncio.run(main())

