let machine = new CoffeeShop.Machine();
let mug = new CoffeeShop.Mug(42);
let mug2 = new CoffeeShop.Mug(42);
let sim = new CoffeeShop.Simulation(machine)

machine.placeMug(mug);

let count = 0;

sim.run(endCondition);

"My Coffeemug is " + mug.hot()+ "(hot) " + mug.full() + "(full) after " + sim.runtime() +
"(Iterations) The other mug is " + mug2.hot()+ "(hot) " + mug2.full() + "(full)";

function endCondition()
{
    return mug.full();
}
