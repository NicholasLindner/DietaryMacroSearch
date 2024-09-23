# Dietary Macro Search Tool

**Project Duration:** November 2023 – January 2024  
**Language:** C++  
**Libraries/Tools Used:** SFML (Simple and Fast Multimedia Library)

## Table of Contents
1. [Overview](#overview)
2. [Features](#features)
3. [Sorting Algorithms](#sorting-algorithms)
4. [Usage](#usage)
5. [Dataset](#dataset)
6. [Recipes](#recipes)
7. [Installation](#installation)

---

## Overview
The **Dietary Macro Search Tool** is a C++ application designed to help users filter and sort food items based on nutritional preferences, specifically targeting macros (carbohydrates, proteins, fats, etc.). The tool leverages efficient sorting algorithms, such as Merge Sort and Heap Sort, to process large datasets, offering quick sorting and selection of foods that meet specific macro criteria.

This project not only showcases the efficiency of sorting algorithms but also allows users to explore recipes that match their macro requirements, making it a practical tool for anyone interested in tracking or optimizing their nutrition.

---

## Features
- **Food Selection by Macros:** Users can filter food items based on their desired macro preferences (carbs, proteins, fats, etc.).
- **Sorting Algorithms:** The tool uses both **Merge Sort** and **Heap Sort** to efficiently process large food datasets.
- **Performance Metrics:** The application displays the runtime of each sorting algorithm after execution, allowing users to compare their efficiency.
- **Sorted Food List:** After sorting, the tool provides a list of foods ordered by the specified macro values.
- **Recipe Recommendations:** Based on the user's macro requirements, the tool suggests recipes that fit within the chosen nutritional parameters.
- **Intuitive Interface:** The tool is powered by SFML to offer an easy-to-use graphical interface, making it user-friendly.

---

## Sorting Algorithms
The tool implements two sorting algorithms for processing the food macro data:

1. **Merge Sort:**  
   A divide-and-conquer algorithm that recursively divides the dataset into smaller subsets, sorts them, and merges them back together. It's highly efficient for large datasets with a time complexity of O(n log n).

2. **Heap Sort:**  
   A comparison-based sorting technique based on a binary heap data structure. It has a similar time complexity of O(n log n) and ensures that sorting is done in place, making it memory efficient.

After each algorithm is executed, the program will output:
- The sorted list of foods based on the chosen macro.
- The runtime of the algorithm, so users can compare the performance of Merge Sort and Heap Sort.

---

## Usage
1. Launch the application.
2. Select a macro category (e.g., carbohydrates, proteins, fats) that you want to filter foods by.
3. Choose a sorting algorithm (Merge Sort or Heap Sort) to sort the foods based on the selected macro.
4. The tool will display:
   - The sorted list of food items based on the selected macro.
   - The runtime of the selected sorting algorithm.
5. Optionally, explore the **Recipe Recommendations** section to find dishes that fit within your desired macro ranges.

---

## Dataset
The dataset used in this tool consists of a large collection of food items, each with detailed macro information:
- Carbohydrates (g)
- Proteins (g)
- Fats (g)
- Calories

You can easily update the dataset or add your own by modifying the CSV file located in the project directory. Ensure that each entry follows the format of the provided dataset for smooth operation.

---

## Recipes
The **Recipe Recommendation** feature suggests meals that match your desired macro ratios. The recipes are generated based on your macro input, ensuring that the suggested meals align with your dietary goals.

---
