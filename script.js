const carData = [
    { id: 1, make: 'Toyota', model: 'Camry', year: 2021, capacity: 5 },
    { id: 2, make: 'Honda', model: 'Civic', year: 2022, capacity: 4 },
    { id: 3, make: 'Ford', model: 'Fusion', year: 2020, capacity: 5 }
];

const driverData = [
    { id: 1, name: 'John Doe', license: 'XYZ123' },
    { id: 2, name: 'Jane Smith', license: 'ABC456' }
];

const bookings = [];

function login() {
    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;
    const loginMessage = document.getElementById('login-message');

    if (username === 'admin' && password === 'admin123') {
        document.getElementById('login-section').classList.add('hidden');
        document.getElementById('admin-section').classList.remove('hidden');
        loginMessage.textContent = '';
    } else if (username === 'abhay' && password === 'au23b1003') {
        document.getElementById('login-section').classList.add('hidden');
        document.getElementById('passenger-section').classList.remove('hidden');
        loginMessage.textContent = '';
    } else {
        loginMessage.textContent = 'Invalid credentials!';
        loginMessage.style.color = 'red';
    }
}

function logout() {
    document.getElementById('login-section').classList.remove('hidden');
    document.getElementById('admin-section').classList.add('hidden');
    document.getElementById('passenger-section').classList.add('hidden');
}

function showAddCar() {
    const carId = prompt('Enter Car ID:');
    const make = prompt('Enter Car Make:');
    const model = prompt('Enter Car Model:');
    const year = prompt('Enter Car Year:');
    const capacity = prompt('Enter Car Capacity:');
    carData.push({ id: carId, make, model, year, capacity });
    alert('Car added successfully!');
}

function showRemoveCar() {
    const carId = prompt('Enter Car ID to remove:');
    const index = carData.findIndex(car => car.id == carId);
    if (index > -1) {
        carData.splice(index, 1);
        alert('Car removed successfully!');
    } else {
        alert('Car not found!');
    }
}

function showAddDriver() {
    const driverId = prompt('Enter Driver ID:');
    const name = prompt('Enter Driver Name:');
    const license = prompt('Enter Driver License Number:');
    driverData.push({ id: driverId, name, license });
    alert('Driver added successfully!');
}

function showRemoveDriver() {
    const driverId = prompt('Enter Driver ID to remove:');
    const index = driverData.findIndex(driver => driver.id == driverId);
    if (index > -1) {
        driverData.splice(index, 1);
        alert('Driver removed successfully!');
    } else {
        alert('Driver not found!');
    }
}

function viewCars() {
    let carsList = 'Available Cars:\n';
    carData.forEach(car => {
        carsList += `ID: ${car.id}, Make: ${car.make}, Model: ${car.model}, Year: ${car.year}, Capacity: ${car.capacity}\n`;
    });
    alert(carsList);
}

function viewDrivers() {
    let driversList = 'Available Drivers:\n';
    driverData.forEach(driver => {
        driversList += `ID: ${driver.id}, Name: ${driver.name}, License: ${driver.license}\n`;
    });
    alert(driversList);
}

function showSearchCar() {
    const searchTerm = prompt('Enter Make or Model to search:');
    const results = carData.filter(car => car.make.includes(searchTerm) || car.model.includes(searchTerm));
    if (results.length > 0) {
        let searchResults = 'Search Results:\n';
        results.forEach(car => {
            searchResults += `ID: ${car.id}, Make: ${car.make}, Model: ${car.model}, Year: ${car.year}, Capacity: ${car.capacity}\n`;
        });
        alert(searchResults);
    } else {
        alert('No cars found!');
    }
}

function showBookCar() {
    const carId = prompt('Enter Car ID to book:');
    const car = carData.find(car => car.id == carId);
    if (car) {
        const passengerName = prompt('Enter your name:');
        const bookingDate = prompt('Enter booking date (YYYY-MM-DD):');
        bookings.push({ carId, passengerName, bookingDate });
        alert('Car booked successfully!');
    } else {
        alert('Car not found!');
    }
}

function viewInvoice() {
    if (bookings.length > 0) {
        let invoice = 'Booking Invoices:\n';
        bookings.forEach((booking, index) => {
            const car = carData.find(car => car.id == booking.carId);
            invoice += `Invoice ${index + 1}:\n`;
            invoice += `Passenger Name: ${booking.passengerName}\n`;
            invoice += `Car: ${car.make} ${car.model} (${car.year}, Capacity: ${car.capacity})\n`;
            invoice += `Booking Date: ${booking.bookingDate}\n\n`;
        });
        alert(invoice);
    } else {
        alert('No bookings found!');
    }
}