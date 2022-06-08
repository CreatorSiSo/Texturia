use iced::{Color, Container, Sandbox, Text};
use std::{borrow::Cow, path::Path};
use unicode_segmentation::UnicodeSegmentation;

mod editor;
use editor::*;

fn main() -> iced::Result {
	match App::run(iced::Settings::default()) {
		Ok(_) => iced::Result::Ok(()),
		Err(error) => iced::Result::Err(error),
	}
}

#[derive(Debug)]
enum Message {
	ButtonPressed,
	ToggleDebug,
}

#[derive(Debug)]
struct App {
	current_file_path: &'static Path,
	saved: bool,
	debug: bool,
	editors: Vec<Editor>,
}

impl Sandbox for App {
	type Message = Message;

	fn new() -> Self {
		App {
			current_file_path: Path::new("ÄÜÖ0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZÖÜÄÄÜÖ0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZÖÜÄÄÜÖ0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZÖÜÄ"),
			saved: false,
			debug: false,
			editors: vec![
				Editor {
					editor_type: EditorType::Settings,
					maximised: false,
				},
				Editor {
					editor_type: EditorType::Nodes,
					maximised: false,
				},
			],
		}
	}

	fn title(&self) -> String {
		let path: &str = &self.current_file_path.to_string_lossy();
		let graphemes = path.graphemes(true).collect::<Vec<&str>>();
		format!(
			"Texturia - {}",
			if graphemes.len() >= 100 {
				graphemes[graphemes.len() - 100..].join("")
			} else {
				path.to_string()
			},
		)
	}

	fn update(&mut self, message: Self::Message) {
		match message {
			Message::ToggleDebug => {}
			_ => {}
		}
	}

	fn view(&mut self) -> iced::Element<'_, Self::Message> {
		Container::new(Text::new("Texturia").color(Color::WHITE)).into()
	}

	fn background_color(&self) -> Color {
		Color::from_rgb(0.2, 0.2, 0.2)
	}
}
