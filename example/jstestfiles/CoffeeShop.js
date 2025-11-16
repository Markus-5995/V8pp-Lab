

let machine = new CoffeeShop.Machine();
let mug = new CoffeeShop.Mug(42);
let sim = new CoffeeShop.Simulation(machine)

machine.placeMug(mug);

sim.run(endCondition);

"My Coffeemug is " + mug.hot()+ "(hot) " + mug.full() + "(full) after " + sim.runtime();



function endCondition()
{
    return true;
}
