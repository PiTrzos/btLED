package com.example.rgbcontroller


interface Navigable {
    enum class Destination{
    List
}
    fun navigate(to: Destination)
}