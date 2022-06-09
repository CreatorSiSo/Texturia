use crate::utils::*;

use iced::pure::{container, row, Element, Sandbox};
use iced::{container, widget, Background, Color, Length, Padding, Text};

#[derive(Debug)]
pub struct Editor {
	pub name: String,
	pub maximised: bool,
}

pub struct Message {}

impl Editor {
	pub fn new(name: String) -> Self {
		Self {
			name,
			maximised: false,
		}
	}

	pub fn view<'a>(&self) -> Element<'a, Message> {
		widget::Container::new(Text::new("Texturia").color(Color::WHITE))
			.width(Length::Fill)
			.height(Length::Fill)
			.padding(Padding::new(5))
			.style(EditorStyle())
      .into()
	}
}

pub struct EditorStyle();

impl container::StyleSheet for EditorStyle {
	fn style(&self) -> container::Style {
		container::Style {
			background: Some(Background::Color(Color::from_rgb(0.2, 0.2, 0.2))),
			border_radius: 5.0,
			border_width: 1.0,
			..default()
		}
	}
}
