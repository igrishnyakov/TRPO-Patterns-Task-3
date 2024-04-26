#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Potato;
class Beet;
class Onion;
class Mayonnaise;
class Fish;

// Базовый класс для ингредиентов
class Ingredient {
public:
    Ingredient(const string& name, double calories_per_100g, double amount)
        : name_(name), calories_per_100g_(calories_per_100g), amount_(amount) {}

    virtual ~Ingredient() {}

    const string& getName() const {
        return name_;
    }

    double getCaloriesPer100g() const {
        return calories_per_100g_;
    }

    double getAmount() const {
        return amount_;
    }

    // Метод для принятия посетителя
    virtual void accept(class Visitor& visitor) const = 0;

private:
    string name_;
    double calories_per_100g_;
    double amount_;
};

// Посетитель - интерфейс операций
class Visitor {
public:
    virtual void visit(const Potato& potato) const = 0;
    virtual void visit(const Beet& beet) const = 0;
    virtual void visit(const Onion& onion) const = 0;
    virtual void visit(const Mayonnaise& mayonnaise) const = 0;
    virtual void visit(const Fish& fish) const = 0;
    virtual ~Visitor() {}
};

// Конкретные продукты
class Potato : public Ingredient {
public:
    Potato(double amount) : Ingredient("Potato", 77.0, amount) {}
    void accept(class Visitor& visitor) const override { visitor.visit(*this); }
};

class Beet : public Ingredient {
public:
    Beet(double amount) : Ingredient("Beet", 43.0, amount) {}
    void accept(class Visitor& visitor) const override { visitor.visit(*this); }
};

class Onion : public Ingredient {
public:
    Onion(double amount) : Ingredient("Onion", 40.0, amount) {}
    void accept(class Visitor& visitor) const override { visitor.visit(*this); }
};

class Mayonnaise : public Ingredient {
public:
    Mayonnaise(double amount) : Ingredient("Mayonnaise", 680.0, amount) {}
    void accept(class Visitor& visitor) const override { visitor.visit(*this); }
};

class Fish : public Ingredient {
public:
    Fish(double amount) : Ingredient("Fish", 170.0, amount) {}
    void accept(class Visitor& visitor) const override { visitor.visit(*this); }
};

// Класс рецепта блюда
class Recipe {
public:
    void addIngredient(const Ingredient* ingredient) {
        ingredients.push_back(ingredient);
    }

    void accept(Visitor& visitor) const {
        for (const Ingredient* ingredient : ingredients) {
            ingredient->accept(visitor);
        }
    }

    vector<const Ingredient*>::const_iterator begin() const {
        return ingredients.begin();
    }

    vector<const Ingredient*>::const_iterator end() const {
        return ingredients.end();
    }

private:
    vector<const Ingredient*> ingredients;
};

// Конкретный посетитель для вывода информации о рецепте
class RecipeVisitor : public Visitor {
public:
    void visit(const Potato& potato) const override { cout << "Potato: " << potato.getAmount() << " g" << endl; }
    void visit(const Beet& beet) const override { cout << "Beet: " << beet.getAmount() << " g" << endl; }
    void visit(const Onion& onion) const override { cout << "Onion: " << onion.getAmount() << " g" << endl; }
    void visit(const Mayonnaise& mayonnaise) const override { cout << "Mayonnaise: " << mayonnaise.getAmount() << " g" << endl; }
    void visit(const Fish& fish) const override { cout << "Fish: " << fish.getAmount() << " g" << endl; }
};

// Конкретный посетитель для подсчета калорий рецепта
class RecipeCaloriesVisitor : public Visitor {
public:
    RecipeCaloriesVisitor() : total_calories_(0.0) {}

    void visit(const Potato& potato) const override {
        total_calories_ += (potato.getCaloriesPer100g() / 100.0) * potato.getAmount();
    }

    void visit(const Beet& beet) const override {
        total_calories_ += (beet.getCaloriesPer100g() / 100.0) * beet.getAmount();
    }

    void visit(const Onion& onion) const override {
        total_calories_ += (onion.getCaloriesPer100g() / 100.0) * onion.getAmount();
    }

    void visit(const Mayonnaise& mayonnaise) const override {
        total_calories_ += (mayonnaise.getCaloriesPer100g() / 100.0) * mayonnaise.getAmount();
    }

    void visit(const Fish& fish) const override {
        total_calories_ += (fish.getCaloriesPer100g() / 100.0) * fish.getAmount();
    }

    double getTotalCalories() const {
        return total_calories_;
    }

private:
    mutable double total_calories_; 
};

int main() {
    Recipe recipe;
    recipe.addIngredient(new Potato(200.0));
    recipe.addIngredient(new Beet(150.0));
    recipe.addIngredient(new Onion(100.0));
    recipe.addIngredient(new Mayonnaise(50.0));
    recipe.addIngredient(new Fish(300.0));

    RecipeVisitor recipeVisitor;
    recipe.accept(recipeVisitor);

    RecipeCaloriesVisitor caloriesVisitor;
    recipe.accept(caloriesVisitor);
    double total_calories = caloriesVisitor.getTotalCalories();
    cout << "Total calories: " << total_calories << endl;

    // Освобождаем память
    for (const Ingredient* ingredient : recipe) {
        delete ingredient;
    }

    return 0;
}