<template>
	<v-form>

		<v-row>
			<v-col>

				<s-data-table
					data="config.project.i18n.strings"
					:fields="fields"
					sort-by="id"
					sort-asc
					label="Translations"
				></s-data-table>

			</v-col>
		</v-row>

	</v-form>
</template>

<script>
	module.exports = {
		data: () => ({
			fields: [
				{
					label: 'ID',
					key: 'id'
				},
				{
					label: 'Translations',
					key: 'translations',
					type: 'array',
					items: [
						{
							label: 'Language',
							key: 'language',
							type: 'text',
							editable: false
						},
						{
							label: 'Translations',
							key: 'translation',
							type: 'text'
						}
					]
				},
			]
		})
	}
</script>

<style scoped>
</style>