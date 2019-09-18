<template>
	<v-form>

		<v-row>
			<v-col>

				<s-data-table
					:data.sync="data.config.project.i18n.strings"
					:compare="data.lastSavedConfig.project.i18n.strings"
					:i18n="i18n"
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
		props: [
			'data',
			'i18n'
		],
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
							text: 'EN',
							value: 'en'
						},
						{
							text: 'DE',
							value: 'de'
						}
					]
				},
			]
		})
	}
</script>

<style scoped>
</style>